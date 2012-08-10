/*
 * Copyright 2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _HAIKU_BUILD_H
#define _HAIKU_BUILD_H


#include <HaikuHostBuildConfig.h>


#define _HAIKU_BUILD_STRING(string)
#define _HAIKU_BUILD_ASMNAME(name) \
	_HAIKU_BUILD_STRING(__USER_LABEL_PREFIX__) name


#ifdef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
#	define _HAIKU_BUILD_DECLARE_FUNCTION(returnValue, name, parameters)	\
		returnValue _haiku_build_##name parameters;
#	define _HAIKU_BUILD_DECLARE_FUNCTION_ETC(returnValue, name, parameters, etc)	\
		returnValue _haiku_build_##name parameters etc;
#	define _HAIKU_BUILD_DECLARE_VARIABLE(type, name) \
		extern type _haiku_build_##name;
#	define _HAIKU_BUILD_DECLARE_VARIABLE_ETC(type, name, etc) \
		extern type _haiku_build_##name etc;
#	define _HAIKU_BUILD_IDENTIFIER(name) _haiku_build_##name
#else
#	define _HAIKU_BUILD_DECLARE_FUNCTION(returnValue, name, parameters)	\
		returnValue _haiku_build_##name parameters;						\
		returnValue name parameters										\
			__asm__(_HAIKU_BUILD_ASMNAME("_haiku_build_" #name));
#	define _HAIKU_BUILD_DECLARE_FUNCTION_ETC(returnValue, name, parameters, etc)	\
		returnValue _haiku_build_##name parameters etc;						\
		returnValue name parameters	etc									\
			__asm__(_HAIKU_BUILD_ASMNAME("_haiku_build_" #name));
#	define _HAIKU_BUILD_DECLARE_VARIABLE(type, name) \
		extern type _haiku_build_##name; \
		extern type name \
			__asm__(_HAIKU_BUILD_ASMNAME("_haiku_build_" #name));
#	define _HAIKU_BUILD_DECLARE_VARIABLE_ETC(type, name, etc) \
		extern type _haiku_build_##name etc; \
		extern type name etc \
			__asm__(_HAIKU_BUILD_ASMNAME("_haiku_build_" #name));
#	define _HAIKU_BUILD_IDENTIFIER(name) name
#endif

#endif	/* _HAIKU_BUILD_H */
