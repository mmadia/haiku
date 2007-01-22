/* ntfsdir.h - directory functions
 *
 * Copyright (c) 2006 Troeglazov Gerasim (3dEyes**)
 *
 * This program/include file is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program/include file is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program (in the main directory of the Linux-NTFS
 * distribution in the file COPYING); if not, write to the Free Software
 * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
#ifndef _NTFSDIR_H
#define _NTFSDIR_H


typedef struct dircookie
{
	u64					pos;
	int					readed;		
	ino_t				ino;
	BOOL 				show_sys_files;	
	char 				name[MAX_PATH];
} dircookie;

status_t fs_free_dircookie( void *_ns, void *node, void *cookie );
status_t fs_opendir( void *_ns, void *_node, void **_cookie );
status_t fs_closedir( void *_ns, void *node, void *_cookie );
status_t fs_rewinddir( void *_ns, void *_node, void *_cookie );
status_t fs_readdir( void *_ns, void *_node, void *_cookie, struct dirent *buf, size_t bufsize, uint32 *num );

#endif
