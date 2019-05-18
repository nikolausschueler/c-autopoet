dnl Process this file with autoconf to produce a configure script.
AC_INIT(lib/poet.c)
AC_CONFIG_HEADERS([config.h])

dnl Checks for programs.
AC_PROG_MAKE_SET
AC_PROG_CC
AC_CHECK_PROG(doxygen_is_here, doxygen, yes, no)
if test $doxygen_is_here = no; then
  AC_MSG_WARN(doxygen was not found so documentation can not be made)
fi

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([getopt.h])

AC_OUTPUT()
