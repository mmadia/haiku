#include <target_SupportDefs.h>


_haiku_build_int32
_haiku_build_atomic_set(_haiku_build_vint32 *value, _haiku_build_int32 newValue)
{
	_haiku_build_int32 oldValue = *value;
	*value = newValue;
	return oldValue;
}


_haiku_build_int32
_haiku_build_atomic_test_and_set(_haiku_build_vint32 *value,
	_haiku_build_int32 newValue, _haiku_build_int32 testAgainst)
{
	_haiku_build_int32 oldValue = *value;
	if (oldValue == testAgainst)
		*value = newValue;
	return oldValue;
}


_haiku_build_int32
_haiku_build_atomic_add(_haiku_build_vint32 *value, _haiku_build_int32 addValue)
{
	_haiku_build_int32 oldValue = *value;
	*value += addValue;
	return oldValue;
}


_haiku_build_int32
_haiku_build_atomic_and(_haiku_build_vint32 *value, _haiku_build_int32 andValue)
{
	_haiku_build_int32 oldValue = *value;
	*value &= andValue;
	return oldValue;
}


_haiku_build_int32
_haiku_build_atomic_or(_haiku_build_vint32 *value, _haiku_build_int32 orValue)
{
	_haiku_build_int32 oldValue = *value;
	*value |= orValue;
	return oldValue;
}


_haiku_build_int32
_haiku_build_atomic_get(_haiku_build_vint32 *value)
{
	return *value;
}


_haiku_build_int64
_haiku_build_atomic_set64(_haiku_build_vint64 *value, _haiku_build_int64 newValue)
{
	_haiku_build_int64 oldValue = *value;
	*value = newValue;
	return oldValue;
}

_haiku_build_int64
_haiku_build_atomic_test_and_set64(_haiku_build_vint64 *value,
	_haiku_build_int64 newValue, _haiku_build_int64 testAgainst)
{
	_haiku_build_int64 oldValue = *value;
	if (oldValue == testAgainst)
		*value = newValue;
	return oldValue;
}

_haiku_build_int64
_haiku_build_atomic_add64(_haiku_build_vint64 *value, _haiku_build_int64 addValue)
{
	_haiku_build_int64 oldValue = *value;
	*value += addValue;
	return oldValue;
}

_haiku_build_int64
_haiku_build_atomic_and64(_haiku_build_vint64 *value, _haiku_build_int64 andValue)
{
	_haiku_build_int64 oldValue = *value;
	*value &= andValue;
	return oldValue;
}

_haiku_build_int64
_haiku_build_atomic_or64(_haiku_build_vint64 *value, _haiku_build_int64 orValue)
{
	_haiku_build_int64 oldValue = *value;
	*value |= orValue;
	return oldValue;
}

_haiku_build_int64
_haiku_build_atomic_get64(_haiku_build_vint64 *value)
{
	return *value;
}
