dnl Process this file with autoconf to produce a configure script.
AC_INIT(lib/poet.c)
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE(poet, 0.1)

dnl Note the blank! Without it, all values are concentated without space in
dnl between.
CFLAGS+=" `pkg-config --cflags glib-2.0`"
LDFLAGS+=" `pkg-config --libs glib-2.0`"

dnl This is for Valgrind.
CFLAGS+=" -g -O0"

dnl Checks for programs.
AC_PROG_MAKE_SET
AC_PROG_CC
AM_PROG_LIBTOOL
AC_CHECK_PROG(doxygen_is_here, doxygen, yes, no)
if test $doxygen_is_here = no; then
  AC_MSG_WARN(doxygen was not found so documentation can not be made)
fi

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([getopt.h])

AC_OUTPUT(Makefile lib/Makefile app/Makefile test/Makefile)
