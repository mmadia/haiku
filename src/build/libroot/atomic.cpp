//#include <BeOSBuildCompatibility.h>

//#include <string.h>

//#include <OS.h>
#include <SupportDefs.h>


haiku_build_int32
_haiku_build_atomic_set(haiku_build_vint32 *value, haiku_build_int32 newValue)
{
	haiku_build_int32 oldValue = *value;
	*value = newValue;
	return oldValue;
}


haiku_build_int32
_haiku_build_atomic_test_and_set(haiku_build_vint32 *value,
	haiku_build_int32 newValue, haiku_build_int32 testAgainst)
{
	haiku_build_int32 oldValue = *value;
	if (oldValue == testAgainst)
		*value = newValue;
	return oldValue;
}


haiku_build_int32
_haiku_build_atomic_add(haiku_build_vint32 *value, haiku_build_int32 addValue)
{
	haiku_build_int32 oldValue = *value;
	*value += addValue;
	return oldValue;
}


haiku_build_int32
_haiku_build_atomic_and(haiku_build_vint32 *value, haiku_build_int32 andValue)
{
	haiku_build_int32 oldValue = *value;
	*value &= andValue;
	return oldValue;
}


haiku_build_int32
_haiku_build_atomic_or(haiku_build_vint32 *value, haiku_build_int32 orValue)
{
	haiku_build_int32 oldValue = *value;
	*value |= orValue;
	return oldValue;
}


haiku_build_int32
_haiku_build_atomic_get(haiku_build_vint32 *value)
{
	return *value;
}


haiku_build_int64
_haiku_build_atomic_set64(haiku_build_vint64 *value, haiku_build_int64 newValue)
{
	haiku_build_int64 oldValue = *value;
	*value = newValue;
	return oldValue;
}

haiku_build_int64
_haiku_build_atomic_test_and_set64(haiku_build_vint64 *value,
	haiku_build_int64 newValue, haiku_build_int64 testAgainst)
{
	haiku_build_int64 oldValue = *value;
	if (oldValue == testAgainst)
		*value = newValue;
	return oldValue;
}

haiku_build_int64
_haiku_build_atomic_add64(haiku_build_vint64 *value, haiku_build_int64 addValue)
{
	haiku_build_int64 oldValue = *value;
	*value += addValue;
	return oldValue;
}

haiku_build_int64
_haiku_build_atomic_and64(haiku_build_vint64 *value, haiku_build_int64 andValue)
{
	haiku_build_int64 oldValue = *value;
	*value &= andValue;
	return oldValue;
}

haiku_build_int64
_haiku_build_atomic_or64(haiku_build_vint64 *value, haiku_build_int64 orValue)
{
	haiku_build_int64 oldValue = *value;
	*value |= orValue;
	return oldValue;
}

haiku_build_int64
_haiku_build_atomic_get64(haiku_build_vint64 *value)
{
	return *value;
}
