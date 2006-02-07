AC_PREREQ(2.59)
AC_INIT(main.c)
#AC_INIT(cpsc532hw2,1.0,Sumit-Khanna@utc.edu)
AM_INIT_AUTOMAKE(cpsc532hw2,1.0)
#AM_CONFIG_HEADER(config.h)

AC_CONFIG_SRCDIR([src/count.h])
AC_CONFIG_HEADER([config.h])
AC_PROG_CC
AC_LANG_C
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])
AC_FUNC_FORK
AC_FUNC_MALLOC

AC_ARG_WITH(wc,[ --with-wc       enables wc])
#AC_ARG_WITH(wc, [AC_HELP_STRING(--with-wc, [compile with wc backend <default=no>]), with_wc=no,with_wc=yes)
AC_PATH_PROG(wc, wc)
#AS_IF([test "x$with_wc" == xyes],
#  AC_DEFINE(HAVE_WC,1,[Define if you want to use wc as backend])
#)
#if test "$ac_with_wc" = yes; then
#    if test x$ac_cv_prog_wc = xyes; then
#       AC_DEFINE(HAVE_WC,[],[Enable wc backend])
#    fi
#fi

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
