#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(csc4800program2,1.0,sumdog@gmail.com)
AC_CONFIG_SRCDIR([src/])
AM_INIT_AUTOMAKE(csc4800program2,1.0)
#AM_CONFIG_HEADER([config.hpp])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CPP

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([netdb.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.
AC_HEADER_STDC
AC_CHECK_FUNCS([gethostbyname gethostname memset socket])

#AC_CONFIG_FILES([Makefile
#                 src/Makefile])
AC_OUTPUT(Makefile src/Makefile)
