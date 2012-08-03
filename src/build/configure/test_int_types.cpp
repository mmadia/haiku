/*
 * Copyright 2011, Ingo Weinhold, ingo_weinhold@gmx.de.
 * Distributed under the terms of the MIT License.
 */


#include <inttypes.h>
#include <stdio.h>


template<typename Type>
struct TypeInfo {
	static const char* const TypeName();
	static const char* const Prefix();
};


#define DEFINE_TYPE_INFO_TEMPLATE(type, prefix)	\
	template<>									\
	struct TypeInfo<type> {						\
		static const char* const TypeName()		\
		{										\
			return #type;						\
		}										\
		static const char* const Prefix()		\
		{										\
			return prefix;						\
		}										\
	};

#define DEFINE_TYPE_INFO_TEMPLATE_SIGNED_AND_UNSIGNED(type, prefix)	\
	DEFINE_TYPE_INFO_TEMPLATE(type, prefix)							\
	DEFINE_TYPE_INFO_TEMPLATE(unsigned type, prefix)


DEFINE_TYPE_INFO_TEMPLATE_SIGNED_AND_UNSIGNED(char, "")
DEFINE_TYPE_INFO_TEMPLATE(signed char, "")
DEFINE_TYPE_INFO_TEMPLATE_SIGNED_AND_UNSIGNED(short, "")
DEFINE_TYPE_INFO_TEMPLATE_SIGNED_AND_UNSIGNED(int, "")
DEFINE_TYPE_INFO_TEMPLATE_SIGNED_AND_UNSIGNED(long, "l")
DEFINE_TYPE_INFO_TEMPLATE_SIGNED_AND_UNSIGNED(long long, "ll")


template<typename Type>
struct PrintTypeInfo {
	static void Print(const char* name)
	{
		printf("#define _HAIKU_BUILD_FEATURE_%s %s\n", name,
			TypeInfo<Type>::TypeName());
		printf("#define _HAIKU_BUILD_FEATURE_FORMAT_PREFIX_%s \"%s\"\n", name,
			TypeInfo<Type>::Prefix());
	}
};


#define PRINT_TYPE_INFO(type)	PrintTypeInfo<type##_t>::Print(#type)

#define PRINT_TYPE_INFO_SIGNED_AND_UNSIGNED(type)	\
	PRINT_TYPE_INFO(type);							\
	PRINT_TYPE_INFO(u##type)


int
main()
{
	PRINT_TYPE_INFO_SIGNED_AND_UNSIGNED(int8);
	PRINT_TYPE_INFO_SIGNED_AND_UNSIGNED(int16);
	PRINT_TYPE_INFO_SIGNED_AND_UNSIGNED(int32);
	PRINT_TYPE_INFO_SIGNED_AND_UNSIGNED(int64);
	return 0;
}
