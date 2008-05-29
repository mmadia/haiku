/*
 * Copyright 2002, Thomas Kurschel. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef __SCSI_PERIPH_INT_H__
#define __SCSI_PERIPH_INT_H__


#include <scsi_periph.h>
#include <block_io.h>
#include <device_manager.h>

#include <stddef.h>

#include "wrapper.h"


typedef struct scsi_periph_device_info {
	struct scsi_periph_handle_info *handles;

	scsi_device scsi_device;
	scsi_device_interface *scsi;
	periph_device_cookie periph_device;
	device_node *node;

	bool removal_requested;

	bool removable;			// true, if device is removable

	int32 rw10_enabled;		// 10 byte r/w commands supported; access must be atomic
	int32 next_tag_action;	// queuing flag for next r/w command; access must be atomic

	mutex mutex;
	int std_timeout;

	scsi_periph_callbacks *callbacks;
} scsi_periph_device_info;

typedef struct scsi_periph_handle_info {
	scsi_periph_device_info *device;
	struct scsi_periph_handle_info *next, *prev;

	int pending_error;		// error to be reported on all accesses
							// (used to block access after medium change until
							//  B_GET_MEDIA_STATUS is called)
	periph_handle_cookie periph_handle;
} scsi_periph_handle_info;

extern device_manager_info *pnp;


// removable.c

void periph_media_changed(scsi_periph_device_info *device, scsi_ccb *ccb);
void periph_media_changed_public(scsi_periph_device_info *device);
status_t periph_get_media_status(scsi_periph_handle_info *handle);
err_res periph_send_start_stop(scsi_periph_device_info *device, scsi_ccb *request,
	bool start, bool with_LoEj);


// error_handling.c

err_res periph_check_error(scsi_periph_device_info *device, scsi_ccb *request);


// handle.c

status_t periph_handle_open(scsi_periph_device_info *device, periph_handle_cookie periph_handle,
	scsi_periph_handle_info **res_handle);
status_t periph_handle_close(scsi_periph_handle_info *handle);
status_t periph_handle_free(scsi_periph_handle_info *handle);


// block.c

status_t periph_check_capacity(scsi_periph_device_info *device, scsi_ccb *ccb);


// device.c

status_t periph_register_device(periph_device_cookie periph_device,
	scsi_periph_callbacks *callbacks, scsi_device scsi_device, scsi_device_interface *scsi,
	device_node *node, bool removable, scsi_periph_device *driver);
status_t periph_unregister_device(scsi_periph_device_info *driver);
char *periph_compose_device_name(device_node *device_node, const char *prefix);


// io.c

status_t periph_read(scsi_periph_handle_info *handle, const phys_vecs *vecs,
	off_t pos, size_t num_blocks, uint32 block_size, size_t *bytes_transferred,
	int preferred_ccb_size);
status_t periph_write(scsi_periph_handle_info *handle, const phys_vecs *vecs,
	off_t pos, size_t num_blocks, uint32 block_size, size_t *bytes_transferred,
	int preferred_ccb_size);
status_t periph_ioctl(scsi_periph_handle_info *handle, int op,
	void *buf, size_t len);
void periph_sync_queue_daemon(void *arg, int iteration);


// scsi_periph.c

status_t periph_safe_exec(scsi_periph_device_info *device, scsi_ccb *request);
status_t periph_simple_exec(scsi_periph_device_info *device, void *cdb,
	uchar cdb_len, void *data, size_t data_len, int ccb_flags);


// device_icons.c

status_t periph_get_icon(icon_type type, device_icon *data);

// sync.c

err_res periph_synchronize_cache(scsi_periph_device_info *device,
	scsi_ccb *request);

#endif	/* __SCSI_PERIPH_INT_H__ */
