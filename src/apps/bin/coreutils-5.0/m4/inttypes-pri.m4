# inttypes-pri.m4 serial 1001 (based on gettext-0.11.4's `serial 1')
dnl Copyright (C) 1997-2002 Free Software Foundation, Inc.
dnl This file is free software, distributed under the terms of the GNU
dnl General Public License.  As a special exception to the GNU General
dnl Public License, this file may be distributed as part of a program
dnl that contains a configuration script generated by Autoconf, under
dnl the same distribution terms as the rest of that program.

dnl From Bruno Haible.

# Define PRI_MACROS_BROKEN if <inttypes.h> exists and defines the PRI*
# macros to non-string values.  This is the case on AIX 4.3.3.

AC_DEFUN([gt_INTTYPES_PRI],
[
  # autoconf-2.52 has a proper check for inttypes.h.
  AC_PREREQ(2.52)

  if test $ac_cv_header_inttypes_h = yes; then
    AC_CACHE_CHECK([whether the inttypes.h PRIxNN macros are broken],
      gt_cv_inttypes_pri_broken,
      [
        AC_TRY_COMPILE([#include <inttypes.h>
#ifdef PRId32
char *p = PRId32;
#endif
], [], gt_cv_inttypes_pri_broken=no, gt_cv_inttypes_pri_broken=yes)
      ])
  fi
  if test "$gt_cv_inttypes_pri_broken" = yes; then
    AC_DEFINE_UNQUOTED(PRI_MACROS_BROKEN, 1,
      [Define if <inttypes.h> exists and defines unusable PRI* macros.])
  fi
])
