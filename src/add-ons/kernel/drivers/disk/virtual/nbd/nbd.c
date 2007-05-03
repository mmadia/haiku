/*
 * Copyright 2006-2007, François Revol. All rights reserved.
 * Distributed under the terms of the MIT License.
 */

/*
 * nbd driver for Haiku
 *
 * Maps a Network Block Device as virtual partitions.
 */

#include <KernelExport.h>
#include <Drivers.h>
#include <Errors.h>
#include <driver_settings.h>
#include <ksocket.h>
#include <netinet/in.h>

#define DEBUG 1

/* locking support */
#ifdef __HAIKU__
#include <kernel/lock.h>
#else
/* wrappers for R5 */
#ifndef _IMPEXP_KERNEL
#define _IMPEXP_KERNEL
#endif
#include "lock.h"
#define benaphore lock
#define benaphore_init new_lock
#define benaphore_destroy free_lock
#define benaphore_lock LOCK
#define benaphore_unlock UNLOCK
#endif

#include "nbd.h"

#define DRV "nbd"
#define DP "nbd:"
#define MAX_NBDS 4
#define DEVICE_PREFIX "disk/virtual/nbd/"
#define DEVICE_FMT DEVICE_PREFIX "%d/raw"
#define DEVICE_NAME_MAX 32
#define MAX_REQ_SIZE (32*1024*1024)
#define BLKSIZE 512

/* debugging */
#if DEBUG
#define PRINT(a) dprintf a
#define WHICH(dev) ((int)(dev - nbd_devices))
#else
#define PRINT(a)
#endif

struct nbd_request_entry {
	struct nbd_request_entry *next;
	struct nbd_request req; /* net byte order */
	struct nbd_reply reply; /* net byte order */
	sem_id sem;
	bool replied;
	bool discard;
	uint64 handle;
	uint32 type;
	uint64 from;
	size_t len;
	void *buffer; /* write: ptr to passed buffer; read: ptr to malloc()ed extra */
};

struct nbd_device {
	char target[64]; // "ip:port"
	struct sockaddr_in server;
	benaphore ben;
	vint32 refcnt;
	uint64 req; /* next ID for requests */
	int sock;
	thread_id postoffice;
	uint64 size;
	struct nbd_request_entry *reqs;
};

typedef struct cookie {
	struct nbd_device *dev;
	
} cookie_t;

/* data=NULL on read */
status_t nbd_alloc_request(struct nbd_device *dev, struct nbd_request_entry **req, uint32 type, off_t from, size_t len, const char *data);
status_t nbd_queue_request(struct nbd_device *dev, struct nbd_request_entry *req);
status_t nbd_dequeue_request(struct nbd_device *dev, uint64 handle, struct nbd_request_entry **req);
status_t nbd_free_request(struct nbd_device *dev, struct nbd_request_entry *req);

struct nbd_device *nbd_find_device(const char* name);

KSOCKET_MODULE_DECL;

/* HACK:
 * In BONE at least, if connect() fails (EINTR or ETIMEDOUT)
 * keeps locked pages around (likely a bone_data,
 * until TCP gets the last ACK). If that happens, we snooze()
 * in unload_driver() to let TCP timeout before the kernel
 * tries to delete the image. */
bool gDelayUnload = false;
#define BONE_TEARDOWN_DELAY 60000000

#pragma mark ==== request manager ====

status_t nbd_alloc_request(struct nbd_device *dev, struct nbd_request_entry **req, uint32 type, off_t from, size_t len, const char *data)
{
	bool w = (type == NBD_CMD_WRITE);
	struct nbd_request_entry *r;
	status_t err = EINVAL;
	uint64 handle;
	PRINT((DP ">%s(%ld, %Ld, %ld)\n", __FUNCTION__, type, from, len));
	
	if (type != NBD_CMD_READ && type != NBD_CMD_WRITE && type != NBD_CMD_DISC)
		return err;
	if (!dev || !req || from < 0)
		return err;
	
	//LOCK
	err = benaphore_lock(&dev->ben);
	if (err)
		return err;

	// atomic
	handle = dev->req++;
	
	
	//UNLOCK
	benaphore_unlock(&dev->ben);
	
	err = ENOMEM;
	r = malloc(sizeof(struct nbd_request_entry) + (w ? 0 : len));
	if (r == NULL)
		goto err0;
	r->next = NULL;
	err = r->sem = create_sem(0, "nbd request sem");
	if (err < 0)
		goto err1;
	
	r->replied = false;
	r->discard = false;
	r->handle = handle;
	r->type = type;
	r->from = from;
	r->len = len;
	
	r->req.magic = B_HOST_TO_BENDIAN_INT32(NBD_REQUEST_MAGIC);
	r->req.type = B_HOST_TO_BENDIAN_INT32(type);
	r->req.handle = B_HOST_TO_BENDIAN_INT64(r->handle);
	r->req.from = B_HOST_TO_BENDIAN_INT64(r->from);
	r->req.len = B_HOST_TO_BENDIAN_INT32(len);
	
	r->buffer = w ? data : (((char *)r) + sizeof(struct nbd_request_entry));
	
	*req = r;
	return B_OK;

err1:
	free(r);
err0:
	dprintf(DP " %s: error 0x%08lx\n", __FUNCTION__, err);
	return err;
}

status_t nbd_queue_request(struct nbd_device *dev, struct nbd_request_entry *req)
{
	PRINT((DP ">%s(handle:%Ld)\n", __FUNCTION__, req->handle));
	req->next = dev->reqs;
	dev->reqs = req;
	return B_OK;
}

status_t nbd_dequeue_request(struct nbd_device *dev, uint64 handle, struct nbd_request_entry **req)
{
	struct nbd_request_entry *r, *prev;
	PRINT((DP ">%s(handle:%Ld)\n", __FUNCTION__, handle));
	r = dev->reqs;
	prev = NULL;
	while (r && r->handle != handle) {
		prev = r;
		r = r->next;
	}
	if (!r)
		return ENOENT;
	
	if (prev)
		prev->next = r->next;
	else
		dev->reqs = r->next;
	
	*req = r;
	return B_OK;
}

status_t nbd_free_request(struct nbd_device *dev, struct nbd_request_entry *req)
{
	PRINT((DP ">%s(handle:%Ld)\n", __FUNCTION__, req->handle));
	delete_sem(req->sem);
	free(req);
	return B_OK;
}



#pragma mark ==== nbd handler ====

int32 nbd_postoffice(void *arg)
{
	struct nbd_device *dev = (struct nbd_device *)arg;
	struct nbd_request_entry *req = NULL;
	struct nbd_reply reply;
	int sock = dev->sock;
	status_t err;
	const char *reason;
	PRINT((DP ">%s()\n", __FUNCTION__));
	
	for (;;) {
		reason = "recv";
		err = krecv(dev->sock, &reply, sizeof(reply), 0);
		if (err == -1 && errno < 0)
			err = errno;
		if (err < 0)
			goto err;
		reason = "recv:size";
		if (err < sizeof(reply))
			err = EINVAL;
		if (err < 0)
			goto err;
		reason = "magic";
		err = EINVAL;
		if (B_BENDIAN_TO_HOST_INT32(reply.magic) != NBD_REPLY_MAGIC)
			goto err;
		
		reason = "lock";
		//LOCK
		err = benaphore_lock(&dev->ben);
		if (err)
			goto err;
		
		reason = "dequeue_request";
		err = nbd_dequeue_request(dev, B_BENDIAN_TO_HOST_INT64(reply.handle), &req);
		
		//UNLOCK
		benaphore_unlock(&dev->ben);
		
		if (!err && !req) {
			dprintf(DP "nbd_dequeue_rquest found NULL!\n");
			err = ENOENT;
		}
		
		if (err == B_OK) {
			memcpy(&req->reply, &reply, sizeof(reply));
			if (req->type == NBD_CMD_READ) {
				err = 0;
				reason = "recv(data)";
				if (reply.error == 0)
					err = krecv(dev->sock, req->buffer, req->len, 0);
				if (err < 0)
					goto err;
				/* tell back how much we've got (?) */
				req->len = err;
			} else {
				if (reply.error)
					req->len = 0;
			}
			
			reason = "lock";
			//LOCK
			err = benaphore_lock(&dev->ben);
			if (err)
				goto err;
			
			// this also must be atomic!
			release_sem(req->sem);
			req->replied = true;
			if (req->discard)
				nbd_free_request(dev, req);
			
			//UNLOCK
			benaphore_unlock(&dev->ben);
		}
		
	}
	
	PRINT((DP "<%s\n", __FUNCTION__));
	return 0;

err:
	dprintf(DP "%s: %s: error 0x%08lx\n", __FUNCTION__, reason, err);
	return err;
}

status_t nbd_connect(struct nbd_device *dev)
{
	struct nbd_init_packet initpkt;
	status_t err;
	PRINT((DP ">%s()\n", __FUNCTION__));

	PRINT((DP " %s: socket()\n", __FUNCTION__));
	err = dev->sock = ksocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (err == -1 && errno < 0)
		err = errno;
	if (err < 0)
		goto err0;
	
	PRINT((DP " %s: connect()\n", __FUNCTION__));
	err = kconnect(dev->sock, (struct sockaddr *)&dev->server, sizeof(dev->server));
	//err = ENOSYS;
	if (err == -1 && errno < 0)
		err = errno;
	/* HACK: avoid the kernel unlading us with locked pages from TCP */
	if (err)
		gDelayUnload = true;
	if (err)
		goto err1;
	
	PRINT((DP " %s: recv(initpkt)\n", __FUNCTION__));
	err = krecv(dev->sock, &initpkt, sizeof(initpkt), 0);
	if (err == -1 && errno < 0)
		err = errno;
	if (err < sizeof(initpkt))
		goto err2;
	err = EINVAL;//EPROTO;
	if (memcmp(initpkt.passwd, NBD_INIT_PASSWD, sizeof(initpkt.passwd)))
		goto err3;
	if (B_BENDIAN_TO_HOST_INT64(initpkt.magic) != NBD_INIT_MAGIC)
		goto err3;
	
	dev->size = B_BENDIAN_TO_HOST_INT64(initpkt.device_size);
	
	dprintf(DP " %s: connected, device size %Ld bytes.\n", __FUNCTION__, dev->size);

	err = dev->postoffice = spawn_kernel_thread(nbd_postoffice, "nbd postoffice", B_REAL_TIME_PRIORITY, dev);
	if (err < B_OK)
		goto err4;
	resume_thread(dev->postoffice);
	
	PRINT((DP "<%s\n", __FUNCTION__));
	return B_OK;
	
err4:
	dev->postoffice = -1;
err3:
err2:
err1:
	kclosesocket(dev->sock);
	dev->sock = -1;
err0:
	dprintf(DP "<%s: error 0x%08lx\n", __FUNCTION__, err);
	return err;
}

status_t nbd_teardown(struct nbd_device *dev)
{
	status_t err, ret;
	PRINT((DP ">%s()\n", __FUNCTION__));
	kshutdown(dev->sock, SHUTDOWN_BOTH);
	kclosesocket(dev->sock);
	dev->sock = -1;
	err = wait_for_thread(dev->postoffice, &ret);
	return B_OK;
}

status_t nbd_post_request(struct nbd_device *dev, struct nbd_request_entry *req)
{
	status_t err;
	PRINT((DP ">%s(handle:%Ld)\n", __FUNCTION__, req->handle));
	
	err = ksend(dev->sock, &req->req, sizeof(req->req), 0);
	if (err < 0)
		return err;
	
	err = nbd_queue_request(dev, req);
	return err;
}


#pragma mark ==== device hooks ====

static struct nbd_device nbd_devices[MAX_NBDS];

status_t nbd_open(const char *name, uint32 flags, cookie_t **cookie) {
	status_t err;
	struct nbd_device *dev = NULL;
	PRINT((DP ">%s(%s, %x, )\n", __FUNCTION__, name, flags));
	(void)name; (void)flags;
	dev = nbd_find_device(name);
	if (!dev)
		return ENOENT;
	err = ENOMEM;
	*cookie = (void*)malloc(sizeof(cookie_t));
	if (*cookie == NULL)
		goto err0;
	memset(*cookie, 0, sizeof(cookie_t));
	(*cookie)->dev = dev;
	err = benaphore_lock(&dev->ben);
	if (err)
		goto err1;
	/*  */
	if (dev->sock < 0)
		err = nbd_connect(dev);
	if (err)
		goto err2;
	dev->refcnt++;
	benaphore_unlock(&dev->ben);
	return B_OK;
	
err2:
	benaphore_unlock(&dev->ben);
err1:
	free(*cookie);
err0:
	dprintf(DP " %s: error 0x%08lx\n", __FUNCTION__, err);
	return err;
}

status_t nbd_close(cookie_t *cookie) {
	struct nbd_device *dev = cookie->dev;
	status_t err;
	PRINT((DP ">%s(%d)\n", __FUNCTION__, WHICH(cookie->dev)));
	
	err = benaphore_lock(&dev->ben);
	if (err)
		return err;
	
	// XXX: do something ?
	
	benaphore_unlock(&dev->ben);
	return B_OK;
}

status_t nbd_free(cookie_t *cookie) {
	struct nbd_device *dev = cookie->dev;
	status_t err;
	PRINT((DP ">%s(%d)\n", __FUNCTION__, WHICH(cookie->dev)));
	
	err = benaphore_lock(&dev->ben);
	if (err)
		return err;
	
	if (--dev->refcnt == 0) {
		err = nbd_teardown(dev);
	}
	
	benaphore_unlock(&dev->ben);
	
	free(cookie);
	return err;
}

status_t nbd_control(cookie_t *cookie, uint32 op, void *data, size_t len) {
	PRINT((DP ">%s(%d, %lu, , %d)\n", __FUNCTION__, WHICH(cookie->dev), op, len));
	switch (op) {
	case B_GET_DEVICE_SIZE: /* this one is broken anyway... */
		if (data) {
			*(size_t *)data = (size_t)cookie->dev->size;
			return B_OK;
		}
		return EINVAL;
	case B_SET_DEVICE_SIZE: /* broken */
		return EINVAL;
	case B_SET_NONBLOCKING_IO:
		return EINVAL;
	case B_SET_BLOCKING_IO:
		return B_OK;
	case B_GET_READ_STATUS:
	case B_GET_WRITE_STATUS:
		if (data) {
			*(bool *)data = false;
			return B_OK;
		}
		return EINVAL;
	case B_GET_GEOMETRY:
	case B_GET_BIOS_GEOMETRY:
		if (data) {
			device_geometry *geom = (device_geometry *)data;
			geom->bytes_per_sector = BLKSIZE;
			geom->sectors_per_track = 1;
			geom->cylinder_count = cookie->dev->size / BLKSIZE;
			geom->head_count = 1;
			geom->device_type = B_DISK;
			geom->removable = false;
			geom->read_only = false; // XXX
			geom->write_once = false;
			return B_OK;
		}
		return EINVAL;
	case B_GET_MEDIA_STATUS:
		if (data) {
			*(status_t *)data = B_OK;
			return B_OK;
		}
		return EINVAL;
		
	case B_EJECT_DEVICE:
	case B_LOAD_MEDIA:
		return B_BAD_VALUE;
	case B_FLUSH_DRIVE_CACHE: /* wait for request list to be empty ? */
		return B_OK;
	default:
		return B_BAD_VALUE;
	}
	return B_NOT_ALLOWED;
}

status_t nbd_read(cookie_t *cookie, off_t position, void *data, size_t *numbytes) {
	struct nbd_device *dev = cookie->dev;
	struct nbd_request_entry *req;
	status_t err, semerr;
	PRINT((DP ">%s(%d, %Ld, , )\n", __FUNCTION__, WHICH(cookie->dev), position));
	
	if (position < 0)
		return EINVAL;
	if (!data)
		return EINVAL;
	
	err = nbd_alloc_request(dev, &req, NBD_CMD_READ, position, *numbytes, NULL);
	if (err)
		goto err0;
	
	//LOCK
	err = benaphore_lock(&dev->ben);
	if (err)
		goto err1;
	
	err = nbd_post_request(dev, req);
	
	//UNLOCK
	benaphore_unlock(&dev->ben);

	if (err)
		goto err2;


	semerr = acquire_sem(req->sem);
	
	//LOCK
	err = benaphore_lock(&dev->ben);
	if(err)
		goto err3;
	
	/* bad scenarii */
	if (!req->replied)
		req->discard = true;
	else if (semerr)
		nbd_free_request(dev, req);
	
	//UNLOCK
	benaphore_unlock(&dev->ben);

	if (semerr == B_OK) {
		*numbytes = req->len;
		memcpy(data, req->buffer, req->len);
		nbd_free_request(dev, req);
		if (*numbytes == 0 && req->reply.error)
			return B_ERROR;
		return B_OK;
	}
	
	*numbytes = 0;
	return semerr;
			

err3:
err2:
err1:
	nbd_free_request(dev, req);
err0:
	*numbytes = 0;
	return err;
}

status_t nbd_write(cookie_t *cookie, off_t position, const void *data, size_t *numbytes) {
	PRINT((DP ">%s(%d, %Ld, , )\n", __FUNCTION__, WHICH(cookie->dev), position));
	(void)cookie; (void)position; (void)data; (void)numbytes;
	*numbytes = 0;
	return EIO;
}

device_hooks nbd_hooks={
	(device_open_hook)nbd_open,
	nbd_close,
	(device_free_hook)nbd_free,
	(device_control_hook)nbd_control,
	(device_read_hook)nbd_read,
	(device_write_hook)nbd_write,
	NULL,
	NULL,
	NULL,
	NULL
};


#pragma mark ==== driver hooks ====

static const char *nbd_name[MAX_NBDS+1] = {
	NULL
};

status_t
init_hardware (void)
{
	PRINT((DP ">%s()\n", __FUNCTION__));
	return B_OK;
}

status_t
init_driver (void)
{
	status_t err;
	int i, j;
	// XXX: load settings
	void *handle;
	PRINT((DP ">%s()\n", __FUNCTION__));

	err = ksocket_init();
	if (err < B_OK)
		return err;
	
	for (i = 0; i < MAX_NBDS; i++) {
		memset(nbd_devices[i].target, 0, 64);
		err = benaphore_init(&nbd_devices[i].ben, "nbd lock");
		if (err < B_OK)
			return err; // XXX
		nbd_devices[i].refcnt = 0;
		nbd_devices[i].req = 0LL; /* next ID for requests */
		nbd_devices[i].sock = -1;
		nbd_devices[i].postoffice = -1;
		nbd_devices[i].size = 0LL;
		nbd_devices[i].reqs = NULL;
		nbd_name[i] = malloc(DEVICE_NAME_MAX);
		if (nbd_name[i] == NULL)
			break;
		sprintf(nbd_name[i], DEVICE_FMT, i);
		/* XXX: default init */
		nbd_devices[i].server.sin_len = sizeof(struct sockaddr_in);
		nbd_devices[i].server.sin_family = AF_INET;
		nbd_devices[i].server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		nbd_devices[i].server.sin_port = htons(1337 + i);
	}
	nbd_name[i] = NULL;
	
	handle = load_driver_settings(DRV);
	if (handle) {
		for (i = 0; i < MAX_NBDS; i++) {
			char keyname[10];
			char *v;
			sprintf(keyname, "nbd%d", i);
			v = get_driver_parameter(handle, keyname, NULL, NULL);
			/* should be "ip:port" */
			// XXX: test
			if (v || 1) {
				//strncpy(nbd_devices[i].target, v, 64);
				//XXX:TEST
				//strncpy(nbd_devices[i].target, "127.0.0.1:1337", 64);
				//XXX:parse it
				nbd_devices[i].server.sin_len = sizeof(struct sockaddr_in);
				nbd_devices[i].server.sin_family = AF_INET;
				nbd_devices[i].server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
				nbd_devices[i].server.sin_port = htons(1337 + i);
			}
		}
		/*should parse as a tree:
		  settings = get_driver_settings(handle);
		  for (i = 0; i < settings->parameter_count; i++) {
		    
		  }
		*/
		
		unload_driver_settings(handle);
	}

	return B_OK;
}

void
uninit_driver (void)
{
	status_t err;
	int i;
	PRINT((DP ">%s()\n", __FUNCTION__));
	for (i = 0; i < MAX_NBDS; i++) {
		free(nbd_name[i]);
		err = benaphore_destroy(&nbd_devices[i].ben);
	}
	err = ksocket_cleanup();
	/* HACK */
	if (gDelayUnload)
		snooze(BONE_TEARDOWN_DELAY);
}

const char**
publish_devices()
{
	PRINT((DP ">%s()\n", __FUNCTION__));
	return nbd_name;
}

device_hooks*
find_device(const char* name)
{
	PRINT((DP ">%s(%s)\n", __FUNCTION__, name));
	return &nbd_hooks;
}

struct nbd_device*
nbd_find_device(const char* name)
{
	int i;
	PRINT((DP ">%s(%s)\n", __FUNCTION__, name));
	for (i = 0; i < MAX_NBDS; i++) {
		if (!strcmp(nbd_name[i], name))
			return &nbd_devices[i];
	}
	return NULL;
}
