AC_PREREQ(2.59)
AC_INIT(cpsc532hw2,1.0,Sumit-Khanna@utc.edu)
AC_CONFIG_SRCDIR([src/count.h])
AC_CONFIG_HEADER([config.h])
AC_PROG_CC
AC_LANG_C
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])
AC_FUNC_FORK
AC_FUNC_MALLOC

AC_ARG_WITH([wc], AC_HELP_STRING([--with-wc], [compile with wc]), with_wc=yes)
AC_PATH_PROG(wc, wc)
if test "$ac_with_wc" = yes; then
    if test x$ac_cv_prog_wc = xyes; then
       AC_DEFINE(HAVE_WC)
    fi
fi

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
