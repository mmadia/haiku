#ifndef FS_IMPL_H
#define FS_IMPL_H

#include <string>

#include <target_SupportDefs.h>

namespace BPrivate {

// defined in fs.cpp

_haiku_build_status_t get_path(int fd, const char *name, std::string &path);

}	// namespace BPrivate

#endif	// FS_IMPL_H
