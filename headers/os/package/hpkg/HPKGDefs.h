/*
 * Copyright 2009,2011, Haiku, Inc.
 * Distributed under the terms of the MIT License.
 */
#ifndef _PACKAGE__HPKG__HPKG_DEFS_H_
#define _PACKAGE__HPKG__HPKG_DEFS_H_


#include <SupportDefs.h>


namespace BPackageKit {

namespace BHPKG {


// magic & version of package and repository files
enum {
	B_HPKG_MAGIC	= 'hpkg',
	B_HPKG_VERSION	= 1,
	//
	B_HPKG_REPO_MAGIC	= 'hpkr',
	B_HPKG_REPO_VERSION	= 1
};


// package attribute IDs
enum BHPKGPackageSectionID {
	B_HPKG_SECTION_HEADER					= 0,
	B_HPKG_SECTION_HEAP						= 1,
	B_HPKG_SECTION_PACKAGE_TOC				= 2,
	B_HPKG_SECTION_PACKAGE_ATTRIBUTES		= 3,
	B_HPKG_SECTION_REPOSITORY_INFO			= 4,
	//
	B_HPKG_SECTION_ENUM_COUNT
};


// attribute types
enum {
	// types
	B_HPKG_ATTRIBUTE_TYPE_INVALID			= 0,
	B_HPKG_ATTRIBUTE_TYPE_INT				= 1,
	B_HPKG_ATTRIBUTE_TYPE_UINT				= 2,
	B_HPKG_ATTRIBUTE_TYPE_STRING			= 3,
	B_HPKG_ATTRIBUTE_TYPE_RAW				= 4,
	//
	B_HPKG_ATTRIBUTE_TYPE_ENUM_COUNT
};


// attribute encodings
enum {
	// signed/unsigned int encodings
	B_HPKG_ATTRIBUTE_ENCODING_INT_8_BIT		= 0,
	B_HPKG_ATTRIBUTE_ENCODING_INT_16_BIT	= 1,
	B_HPKG_ATTRIBUTE_ENCODING_INT_32_BIT	= 2,
	B_HPKG_ATTRIBUTE_ENCODING_INT_64_BIT	= 3,

	// string encodings
	B_HPKG_ATTRIBUTE_ENCODING_STRING_INLINE	= 0,
		// null-terminated string
	B_HPKG_ATTRIBUTE_ENCODING_STRING_TABLE	= 1,
		// unsigned LEB128 index into string table

	// raw data encodings
	B_HPKG_ATTRIBUTE_ENCODING_RAW_INLINE	= 0,
		// unsigned LEB128 size, raw bytes
	B_HPKG_ATTRIBUTE_ENCODING_RAW_HEAP		= 1
		// unsigned LEB128 size, unsigned LEB128 offset into the heap
};


// maximum number of bytes of data to be encoded inline; more will be allocated
// on the heap
#define B_HPKG_MAX_INLINE_DATA_SIZE	8


// name of file containing package information (in package's root folder)
#define B_HPKG_PACKAGE_INFO_FILE_NAME	".PackageInfo"


// package attribute IDs
enum BHPKGAttributeID {
	B_HPKG_ATTRIBUTE_ID_DIRECTORY_ENTRY 			=  0,
	B_HPKG_ATTRIBUTE_ID_FILE_TYPE					=  1,
	B_HPKG_ATTRIBUTE_ID_FILE_PERMISSIONS			=  2,
	B_HPKG_ATTRIBUTE_ID_FILE_USER					=  3,
	B_HPKG_ATTRIBUTE_ID_FILE_GROUP					=  4,
	B_HPKG_ATTRIBUTE_ID_FILE_ATIME					=  5,
	B_HPKG_ATTRIBUTE_ID_FILE_MTIME					=  6,
	B_HPKG_ATTRIBUTE_ID_FILE_CRTIME					=  7,
	B_HPKG_ATTRIBUTE_ID_FILE_ATIME_NANOS			=  8,
	B_HPKG_ATTRIBUTE_ID_FILE_MTIME_NANOS			=  9,
	B_HPKG_ATTRIBUTE_ID_FILE_CRTIM_NANOS			= 10,
	B_HPKG_ATTRIBUTE_ID_FILE_ATTRIBUTE				= 11,
	B_HPKG_ATTRIBUTE_ID_FILE_ATTRIBUTE_TYPE			= 12,
	B_HPKG_ATTRIBUTE_ID_DATA						= 13,
	B_HPKG_ATTRIBUTE_ID_DATA_SIZE					= 14,
	B_HPKG_ATTRIBUTE_ID_DATA_COMPRESSION			= 15,
	B_HPKG_ATTRIBUTE_ID_DATA_CHUNK_SIZE				= 16,
	B_HPKG_ATTRIBUTE_ID_SYMLINK_PATH				= 17,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_NAME				= 18,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_SUMMARY				= 19,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_DESCRIPTION			= 20,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_VENDOR				= 21,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_PACKAGER			= 22,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_FLAGS				= 23,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_ARCHITECTURE		= 24,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_VERSION_MAJOR		= 25,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_VERSION_MINOR		= 26,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_VERSION_MICRO		= 27,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_VERSION_RELEASE		= 28,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_COPYRIGHT			= 29,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_LICENSE				= 30,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_PROVIDES			= 31,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_PROVIDES_TYPE		= 32,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_REQUIRES			= 33,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_SUPPLEMENTS			= 34,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_CONFLICTS			= 35,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_FRESHENS			= 36,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_REPLACES			= 37,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_RESOLVABLE_OPERATOR	= 38,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_CHECKSUM			= 39,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_VERSION_PRE_RELEASE	= 40,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_PROVIDES_COMPATIBLE	= 41,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_URL					= 42,
	B_HPKG_ATTRIBUTE_ID_PACKAGE_SOURCE_URL			= 43,
	//
	B_HPKG_ATTRIBUTE_ID_ENUM_COUNT,
};


// compression types
enum {
	B_HPKG_COMPRESSION_NONE	= 0,
	B_HPKG_COMPRESSION_ZLIB	= 1
};


// file types (B_HPKG_ATTRIBUTE_ID_FILE_TYPE)
enum {
	B_HPKG_FILE_TYPE_FILE		= 0,
	B_HPKG_FILE_TYPE_DIRECTORY	= 1,
	B_HPKG_FILE_TYPE_SYMLINK	= 2
};


// default values
enum {
	B_HPKG_DEFAULT_FILE_TYPE				= B_HPKG_FILE_TYPE_FILE,
	B_HPKG_DEFAULT_FILE_PERMISSIONS			= 0644,
	B_HPKG_DEFAULT_DIRECTORY_PERMISSIONS	= 0755,
	B_HPKG_DEFAULT_SYMLINK_PERMISSIONS		= 0777,
	B_HPKG_DEFAULT_DATA_COMPRESSION			= B_HPKG_COMPRESSION_NONE,
	B_HPKG_DEFAULT_DATA_CHUNK_SIZE_ZLIB		= 64 * 1024
};


// Writer Init() flags
enum {
	B_HPKG_WRITER_UPDATE_PACKAGE	= 0x01,
		// update the package (don't truncate)
	B_HPKG_WRITER_FORCE_ADD			= 0x02,
		// when updating a pre-existing entry, don't fail, but replace the
		// entry, if possible (directories will be merged, but won't replace a
		// non-directory)
};


}	// namespace BHPKG

}	// namespace BPackageKit


#endif	// _PACKAGE__HPKG__HPKG_DEFS_H_
