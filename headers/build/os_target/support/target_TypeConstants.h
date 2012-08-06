/*
 * Copyright 2005-2012, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 *
 * Author:
 *		Erik Jaesler (erik@cgsoftware.com)
 */
#ifndef _TYPE_CONSTANTS_H
#define _TYPE_CONSTANTS_H


#include <target_BeBuild.h>

// NOTE: #8730 -- do enums need a version for #ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER?
enum {
	_HAIKU_BUILD_B_AFFINE_TRANSFORM_TYPE		= 'AMTX',
	_HAIKU_BUILD_B_ALIGNMENT_TYPE				= 'ALGN',
	_HAIKU_BUILD_B_ANY_TYPE						= 'ANYT',
	_HAIKU_BUILD_B_ATOM_TYPE					= 'ATOM',
	_HAIKU_BUILD_B_ATOMREF_TYPE					= 'ATMR',
	_HAIKU_BUILD_B_BOOL_TYPE					= 'BOOL',
	_HAIKU_BUILD_B_CHAR_TYPE					= 'CHAR',
	_HAIKU_BUILD_B_COLOR_8_BIT_TYPE				= 'CLRB',
	_HAIKU_BUILD_B_DOUBLE_TYPE					= 'DBLE',
	_HAIKU_BUILD_B_FLOAT_TYPE					= 'FLOT',
	_HAIKU_BUILD_B_GRAYSCALE_8_BIT_TYPE			= 'GRYB',
	_HAIKU_BUILD_B_INT16_TYPE					= 'SHRT',
	_HAIKU_BUILD_B_INT32_TYPE					= 'LONG',
	_HAIKU_BUILD_B_INT64_TYPE					= 'LLNG',
	_HAIKU_BUILD_B_INT8_TYPE					= 'BYTE',
	_HAIKU_BUILD_B_LARGE_ICON_TYPE				= 'ICON',
	_HAIKU_BUILD_B_MEDIA_PARAMETER_GROUP_TYPE	= 'BMCG',
	_HAIKU_BUILD_B_MEDIA_PARAMETER_TYPE			= 'BMCT',
	_HAIKU_BUILD_B_MEDIA_PARAMETER_WEB_TYPE		= 'BMCW',
	_HAIKU_BUILD_B_MESSAGE_TYPE					= 'MSGG',
	_HAIKU_BUILD_B_MESSENGER_TYPE				= 'MSNG',
	_HAIKU_BUILD_B_MIME_TYPE					= 'MIME',
	_HAIKU_BUILD_B_MINI_ICON_TYPE				= 'MICN',
	_HAIKU_BUILD_B_MONOCHROME_1_BIT_TYPE		= 'MNOB',
	_HAIKU_BUILD_B_OBJECT_TYPE					= 'OPTR',
	_HAIKU_BUILD_B_OFF_T_TYPE					= 'OFFT',
	_HAIKU_BUILD_B_PATTERN_TYPE					= 'PATN',
	_HAIKU_BUILD_B_POINTER_TYPE					= 'PNTR',
	_HAIKU_BUILD_B_POINT_TYPE					= 'BPNT',
	_HAIKU_BUILD_B_PROPERTY_INFO_TYPE			= 'SCTD',
	_HAIKU_BUILD_B_RAW_TYPE						= 'RAWT',
	_HAIKU_BUILD_B_RECT_TYPE					= 'RECT',
	_HAIKU_BUILD_B_REF_TYPE						= 'RREF',
	_HAIKU_BUILD_B_RGB_32_BIT_TYPE				= 'RGBB',
	_HAIKU_BUILD_B_RGB_COLOR_TYPE				= 'RGBC',
	_HAIKU_BUILD_B_SIZE_TYPE					= 'SIZE',
	_HAIKU_BUILD_B_SIZE_T_TYPE					= 'SIZT',
	_HAIKU_BUILD_B_SSIZE_T_TYPE					= 'SSZT',
	_HAIKU_BUILD_B_STRING_TYPE					= 'CSTR',
	_HAIKU_BUILD_B_STRING_LIST_TYPE				= 'STRL',
	_HAIKU_BUILD_B_TIME_TYPE					= 'TIME',
	_HAIKU_BUILD_B_UINT16_TYPE					= 'USHT',
	_HAIKU_BUILD_B_UINT32_TYPE					= 'ULNG',
	_HAIKU_BUILD_B_UINT64_TYPE					= 'ULLG',
	_HAIKU_BUILD_B_UINT8_TYPE					= 'UBYT',
	_HAIKU_BUILD_B_VECTOR_ICON_TYPE				= 'VICN',
	_HAIKU_BUILD_B_XATTR_TYPE					= 'XATR',
	_HAIKU_BUILD_B_NETWORK_ADDRESS_TYPE			= 'NWAD',
	_HAIKU_BUILD_B_MIME_STRING_TYPE				= 'MIMS',

	// deprecated, do not use
	_HAIKU_BUILD_B_ASCII_TYPE					= 'TEXT'	// use B_STRING_TYPE instead
};

// System-wide MIME types for handling URL's

_HAIKU_BUILD_DECLARE_CONSTANT(const char*, B__URL_HTTP) 	// application/x-vnd.Be.URL.http
_HAIKU_BUILD_DECLARE_CONSTANT(const char*, B__URL_HTTPS) 	// application/x-vnd.Be.URL.https
_HAIKU_BUILD_DECLARE_CONSTANT(const char*, B__URL_FTP)		// application/x-vnd.Be.URL.ftp
_HAIKU_BUILD_DECLARE_CONSTANT(const char*, B__URL_GOPHER) 	// application/x-vnd.Be.URL.gopher
_HAIKU_BUILD_DECLARE_CONSTANT(const char*, B__URL_MAILTO) 	// application/x-vnd.Be.URL.mailto
_HAIKU_BUILD_DECLARE_CONSTANT(const char*, B__URL_NEWS)		// application/x-vnd.Be.URL.news
_HAIKU_BUILD_DECLARE_CONSTANT(const char*, B__URL_NNTP)		// application/x-vnd.Be.URL.nntp
_HAIKU_BUILD_DECLARE_CONSTANT(const char*, B__URL_TELNET) 	// application/x-vnd.Be.URL.telnet
_HAIKU_BUILD_DECLARE_CONSTANT(const char*, B__URL_RLOGIN) 	// application/x-vnd.Be.URL.rlogin
_HAIKU_BUILD_DECLARE_CONSTANT(const char*, B__URL_TN3270) 	// application/x-vnd.Be.URL.tn3270
_HAIKU_BUILD_DECLARE_CONSTANT(const char*, B__URL_WAIS)		// application/x-vnd.Be.URL.wais
_HAIKU_BUILD_DECLARE_CONSTANT(const char*, B__URL_FILE)		// application/x-vnd.Be.URL.file

#endif	// _TYPE_CONSTANTS_H
