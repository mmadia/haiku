/*
 * Copyright 2009, Ingo Weinhold, ingo_weinhold@gmx.de.
 * Distributed under the terms of the MIT License.
 */


#include "kernel_interface.h"

#include <dirent.h>

#include <new>

#include <fs_info.h>
#include <fs_interface.h>
#include <KernelExport.h>

#include <AutoDeleter.h>

#include "DebugSupport.h"
#include "Directory.h"
#include "Volume.h"


static const uint32 kOptimalIOSize = 64 * 1024;


// #pragma mark - helper functions


static bool
is_user_in_group(gid_t gid)
{
	gid_t groups[NGROUPS_MAX];
	int groupCount = getgroups(NGROUPS_MAX, groups);
	for (int i = 0; i < groupCount; i++) {
		if (gid == groups[i])
			return true;
	}

	return (gid == getegid());
}


static bool
set_dirent_name(struct dirent* buffer, size_t bufferSize, const char* name,
	size_t nameLen)
{
	size_t length = (buffer->d_name + nameLen + 1) - (char*)buffer;
	if (length > bufferSize)
		return false;

	memcpy(buffer->d_name, name, nameLen);
	buffer->d_name[nameLen] = '\0';
	buffer->d_reclen = length;
	return true;
}


//	#pragma mark - Volume


static status_t
packagefs_mount(fs_volume* fsVolume, const char* device, uint32 flags,
	const char* parameters, ino_t* _rootID)
{
	FUNCTION("fsVolume: %p, device: \"%s\", flags: %#lx, parameters: \"%s\"\n",
		fsVolume, device, flags, parameters);

	// create a Volume object
	Volume* volume = new(std::nothrow) Volume(fsVolume);
	if (volume == NULL)
		RETURN_ERROR(B_NO_MEMORY);
	ObjectDeleter<Volume> volumeDeleter(volume);

	status_t error = volume->Mount();
	if (error != B_OK)
		return error;

	// set return values
	*_rootID = volume->RootDirectory()->ID();
	fsVolume->private_volume = volumeDeleter.Detach();
	fsVolume->ops = &gPackageFSVolumeOps;

	return B_OK;
}


static status_t
packagefs_unmount(fs_volume* fsVolume)
{
	Volume* volume = (Volume*)fsVolume->private_volume;

	FUNCTION("volume: %p\n", volume);

	volume->Unmount();
	delete volume;

	return B_OK;
}


static status_t
packagefs_read_fs_info(fs_volume* fsVolume, struct fs_info* info)
{
	FUNCTION("volume: %p, info: %p\n", fsVolume->private_volume, info);

	info->flags = B_FS_IS_READONLY;
	info->block_size = 4096;
	info->io_size = kOptimalIOSize;
	info->total_blocks = info->free_blocks = 1;
	strlcpy(info->volume_name, "Package FS", sizeof(info->volume_name));
	return B_OK;
}


// #pragma mark - VNodes


static status_t
packagefs_lookup(fs_volume* fsVolume, fs_vnode* fsDir, const char* entryName,
	ino_t* _vnid)
{
	Volume* volume = (Volume*)fsVolume->private_volume;
	Node* dir = (Node*)fsDir->private_node;

	FUNCTION("volume: %p, dir: %p (%lld), entry: \"%s\"\n", volume, dir,
		dir->ID(), entryName);

	if (!S_ISDIR(dir->Mode()))
		return B_NOT_A_DIRECTORY;

	// resolve "."
	if (strcmp(entryName, ".") == 0) {
		Node* node;
		*_vnid = dir->ID();
		return volume->GetVNode(*_vnid, node);
	}

	// resolve ".."
	if (strcmp(entryName, "..") == 0) {
		Node* node;
		*_vnid = dir->Parent()->ID();
		return volume->GetVNode(*_vnid, node);
	}

	// resolve normal entries -- look up the node
	NodeReadLocker dirLocker(dir);
	Node* node = dynamic_cast<Directory*>(dir)->FindChild(entryName);
	if (node == NULL)
		return B_ENTRY_NOT_FOUND;
	BReference<Node> nodeReference(node);
	dirLocker.Unlock();

	// get the vnode reference
	*_vnid = node->ID();
	RETURN_ERROR(volume->GetVNode(*_vnid, node));
}


static status_t
packagefs_get_vnode(fs_volume* fsVolume, ino_t vnid, fs_vnode* fsNode,
	int* _type, uint32* _flags, bool reenter)
{
	Volume* volume = (Volume*)fsVolume->private_volume;

	FUNCTION("volume: %p, vnid: %lld\n", volume, vnid);

	VolumeReadLocker volumeLocker(volume);
	Node* node = volume->FindNode(vnid);
	if (node == NULL)
		return B_ENTRY_NOT_FOUND;
	node->AcquireReference();

	fsNode->private_node = node;
	fsNode->ops = &gPackageFSVnodeOps;
	*_type = node->Mode() & S_IFMT;
	*_flags = 0;

	return B_OK;
}


static status_t
packagefs_put_vnode(fs_volume* fsVolume, fs_vnode* fsNode, bool reenter)
{
	Volume* volume = (Volume*)fsVolume->private_volume;
	Node* node = (Node*)fsNode->private_node;

	FUNCTION("volume: %p, node: %p\n", volume, node);
	TOUCH(volume);

	node->ReleaseReference();

	return B_OK;
}


// #pragma mark - Nodes


static status_t
packagefs_read_symlink(fs_volume* fsVolume, fs_vnode* fsNode, char* buffer,
	size_t* bufferSize)
{
	return B_UNSUPPORTED;
}


static status_t
packagefs_access(fs_volume* fsVolume, fs_vnode* fsNode, int mode)
{
	Volume* volume = (Volume*)fsVolume->private_volume;
	Node* node = (Node*)fsNode->private_node;
	TOUCH(volume);

	FUNCTION("volume: %p, node: %p (%lld)\n", volume, node, node->ID());
	TOUCH(volume);

	// write access requested?
	if (mode & W_OK)
		return B_READ_ONLY_DEVICE;

	// get node permissions
	int userPermissions = (node->Mode() & S_IRWXU) >> 6;
	int groupPermissions = (node->Mode() & S_IRWXG) >> 3;
	int otherPermissions = node->Mode() & S_IRWXO;

	// get the permissions for this uid/gid
	int permissions = 0;
	uid_t uid = geteuid();

	if (uid == 0) {
		// user is root
		// root has always read/write permission, but at least one of the
		// X bits must be set for execute permission
		permissions = userPermissions | groupPermissions | otherPermissions
			| S_IROTH | S_IWOTH;
	} else if (uid == node->UserID()) {
		// user is node owner
		permissions = userPermissions;
	} else if (is_user_in_group(node->GroupID())) {
		// user is in owning group
		permissions = groupPermissions;
	} else {
		// user is one of the others
		permissions = otherPermissions;
	}

	return (mode & ~permissions) ? B_NOT_ALLOWED : B_OK;
}


static status_t
packagefs_read_stat(fs_volume* fsVolume, fs_vnode* fsNode, struct stat* st)
{
	Volume* volume = (Volume*)fsVolume->private_volume;
	Node* node = (Node*)fsNode->private_node;

	FUNCTION("volume: %p, node: %p (%lld)\n", volume, node, node->ID());
	TOUCH(volume);

// TODO: Fill in correctly!
	st->st_mode = node->Mode();
	st->st_nlink = 1;
	st->st_uid = 0;
	st->st_gid = 0;
	st->st_size = 0;
	st->st_blksize = kOptimalIOSize;
	st->st_atime = 0;
	st->st_mtime = 0;
	st->st_ctime = 0;
	st->st_crtime = 0;

	return B_OK;
}


// #pragma mark - Files


static status_t
packagefs_open(fs_volume* fsVolume, fs_vnode* fsNode, int openMode,
	void** _cookie)
{
	Volume* volume = (Volume*)fsVolume->private_volume;
	Node* node = (Node*)fsNode->private_node;

	FUNCTION("volume: %p, node: %p (%lld), openMode %#x\n", volume, node,
		node->ID(), openMode);
	TOUCH(volume);
	TOUCH(node);

// TODO: Implement it for real!
	*_cookie = NULL;

	return B_OK;
}


static status_t
packagefs_close(fs_volume* fs, fs_vnode* _node, void* cookie)
{
	return B_OK;
}


static status_t
packagefs_free_cookie(fs_volume* fs, fs_vnode* _node, void* cookie)
{
	return B_OK;
}


static status_t
packagefs_read(fs_volume* fs, fs_vnode* _node, void* cookie, off_t pos,
	void* buffer, size_t* bufferSize)
{
	return B_UNSUPPORTED;
}


// #pragma mark - Directories


struct DirectoryCookie : DirectoryIterator {
	Directory*	directory;
	int32		state;
	bool		registered;

	DirectoryCookie(Directory* directory)
		:
		directory(directory),
		state(0),
		registered(false)
	{
		Rewind();
	}

	~DirectoryCookie()
	{
		if (registered)
			directory->RemoveDirectoryIterator(this);
	}

	void Rewind()
	{
		if (registered)
			directory->RemoveDirectoryIterator(this);
		registered = false;

		state = 0;
		node = directory;
	}

	Node* Current(const char*& _name) const
	{
		if (node == NULL)
			return NULL;

		if (state == 0)
			_name = ".";
		else if (state == 1)
			_name = "..";
		else
			_name = node->Name();

		return node;
	}

	Node* Next()
	{
		if (state == 0) {
			state = 1;
			node = directory->Parent();
			if (node == NULL)
				node = directory;
			return node;
		}

		if (state == 1) {
			node = directory->FirstChild();
			state = 2;
		} else {
			if (node != NULL)
				node = directory->NextChild(node);
		}

		if (node == NULL) {
			if (registered) {
				directory->RemoveDirectoryIterator(this);
				registered = false;
			}

			return NULL;
		}

		if (!registered) {
			directory->AddDirectoryIterator(this);
			registered = true;
		}

		return node;
	}
};


static status_t
packagefs_open_dir(fs_volume* fsVolume, fs_vnode* fsNode, void** _cookie)
{
	Volume* volume = (Volume*)fsVolume->private_volume;
	Node* node = (Node*)fsNode->private_node;

	FUNCTION("volume: %p, node: %p (%lld)\n", volume, node, node->ID());

	if (!S_ISDIR(node->Mode()))
		return B_NOT_A_DIRECTORY;

	Directory* dir = dynamic_cast<Directory*>(node);

	// create a cookie
	DirectoryCookie* cookie = new(std::nothrow) DirectoryCookie(dir);
	if (cookie == NULL)
		RETURN_ERROR(B_NO_MEMORY);

	*_cookie = cookie;
	return B_OK;
}


static status_t
packagefs_close_dir(fs_volume* fsVolume, fs_vnode* fsNode, void* cookie)
{
	return B_OK;
}


static status_t
packagefs_free_dir_cookie(fs_volume* fsVolume, fs_vnode* fsNode, void* _cookie)
{
	Volume* volume = (Volume*)fsVolume->private_volume;
	Node* node = (Node*)fsNode->private_node;
	DirectoryCookie* cookie = (DirectoryCookie*)_cookie;

	FUNCTION("volume: %p, node: %p (%lld), cookie: %p\n", volume, node,
		node->ID(), cookie);
	TOUCH(volume);
	TOUCH(node);

	NodeWriteLocker dirLocker(node);
	delete cookie;

	return B_OK;
}


static status_t
packagefs_read_dir(fs_volume* fsVolume, fs_vnode* fsNode, void* _cookie,
	struct dirent* buffer, size_t bufferSize, uint32* _count)
{
	Volume* volume = (Volume*)fsVolume->private_volume;
	Node* node = (Node*)fsNode->private_node;
	DirectoryCookie* cookie = (DirectoryCookie*)_cookie;

	FUNCTION("volume: %p, node: %p (%lld), cookie: %p\n", volume, node,
		node->ID(), cookie);
	TOUCH(volume);
	TOUCH(node);

	NodeWriteLocker dirLocker(cookie->directory);

	uint32 maxCount = *_count;
	uint32 count = 0;

	dirent* previousEntry = NULL;

	const char* name;
	while (Node* child = cookie->Current(name)) {
		// don't read more entries than requested
		if (count >= maxCount)
			break;

		// align the buffer for subsequent entries
		if (count > 0) {
			addr_t offset = (addr_t)buffer % 8;
			if (offset > 0) {
				offset = 8 - offset;
				if (bufferSize <= offset)
					break;

				previousEntry->d_reclen += offset;
				buffer = (dirent*)((addr_t)buffer + offset);
				bufferSize -= offset;
			}
		}

		// fill in the entry name -- checks whether the entry fits into the
		// buffer
		if (!set_dirent_name(buffer, bufferSize, name, strlen(name))) {
			if (count == 0)
				RETURN_ERROR(B_BUFFER_OVERFLOW);
			break;
		}

		// fill in the other data
		buffer->d_dev = volume->ID();
		buffer->d_ino = child->ID();

		count++;
		previousEntry = buffer;
		bufferSize -= buffer->d_reclen;
		buffer = (dirent*)((addr_t)buffer + buffer->d_reclen);

		cookie->Next();
	}

	*_count = count;
	return B_OK;
}


static status_t
packagefs_rewind_dir(fs_volume* fsVolume, fs_vnode* fsNode, void* _cookie)
{
	Volume* volume = (Volume*)fsVolume->private_volume;
	Node* node = (Node*)fsNode->private_node;
	DirectoryCookie* cookie = (DirectoryCookie*)_cookie;

	FUNCTION("volume: %p, node: %p (%lld), cookie: %p\n", volume, node,
		node->ID(), cookie);
	TOUCH(volume);
	TOUCH(node);

	NodeWriteLocker dirLocker(node);
	cookie->Rewind();

	return B_OK;
}


// #pragma mark - Module Interface


static status_t
packagefs_std_ops(int32 op, ...)
{
	switch (op) {
		case B_MODULE_INIT:
			init_debugging();
			PRINT("package_std_ops(): B_MODULE_INIT\n");
			return B_OK;

		case B_MODULE_UNINIT:
			PRINT("package_std_ops(): B_MODULE_UNINIT\n");
			exit_debugging();
			return B_OK;

		default:
			return B_ERROR;
	}
}


static file_system_module_info sPackageFSModuleInfo = {
	{
		"file_systems/packagefs" B_CURRENT_FS_API_VERSION,
		0,
		packagefs_std_ops,
	},

	"packagefs",				// short_name
	"Package File System",		// pretty_name
	0,							// DDM flags


	// scanning
	NULL,	// identify_partition,
	NULL,	// scan_partition,
	NULL,	// free_identify_partition_cookie,
	NULL,	// free_partition_content_cookie()

	&packagefs_mount
};


fs_volume_ops gPackageFSVolumeOps = {
	&packagefs_unmount,
	&packagefs_read_fs_info,
	NULL,	// write_fs_info,
	NULL,	// sync,

	&packagefs_get_vnode

	// TODO: index operations
	// TODO: query operations
	// TODO: FS layer operations
};


fs_vnode_ops gPackageFSVnodeOps = {
	/* vnode operations */
	&packagefs_lookup,
	NULL,	// get_vnode_name,
	&packagefs_put_vnode,
	&packagefs_put_vnode,	// remove_vnode -- same as put_vnode

	/* VM file access */
	NULL,	// can_page,
	NULL,	// read_pages,
	NULL,	// write_pages,

	NULL,	// io()
	NULL,	// cancel_io()

	NULL,	// get_file_map,

	NULL,	// ioctl,
	NULL,	// set_flags,
	NULL,	// select,
	NULL,	// deselect,
	NULL,	// fsync,

	&packagefs_read_symlink,
	NULL,	// create_symlink,

	NULL,	// link,
	NULL,	// unlink,
	NULL,	// rename,

	&packagefs_access,
	&packagefs_read_stat,
	NULL,	// write_stat,

	/* file operations */
	NULL,	// create,
	&packagefs_open,
	&packagefs_close,
	&packagefs_free_cookie,
	&packagefs_read,
	NULL,	// write,

	/* directory operations */
	NULL,	// create_dir,
	NULL,	// remove_dir,
	&packagefs_open_dir,
	&packagefs_close_dir,
	&packagefs_free_dir_cookie,
	&packagefs_read_dir,
	&packagefs_rewind_dir

	// TODO: attribute directory operations
	// TODO: attribute operations
	// TODO: FS layer operations
};


module_info *modules[] = {
	(module_info *)&sPackageFSModuleInfo,
	NULL,
};
