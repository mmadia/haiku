
//#ifdef BUILDING_FS_SHELL
//#	include "compat.h"
//#else
//#	include <BeOSBuildCompatibility.h>
//#endif

#include <target_ByteOrder.h>

_haiku_build_uint16
_haiku_build___swap_int16(_haiku_build_uint16 value)
{
	return (value >> 8) | (value << 8);
}

_haiku_build_uint32
_haiku_build___swap_int32(_haiku_build_uint32 value)
{
	return (value >> 24) | ((value & 0xff0000) >> 8) | ((value & 0xff00) << 8)
		| (value << 24);
}

_haiku_build_uint64
_haiku_build___swap_int64(_haiku_build_uint64 value)
{
	return _haiku_build_uint64(
			_haiku_build___swap_int32(_haiku_build_uint32(value >> 32)))
		| (_haiku_build_uint64(
			_haiku_build___swap_int32(_haiku_build_uint32(value))) << 32);
}
