#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
m4_include(libcurl.m4)
AC_PREREQ([2.68])
AC_INIT([resfix], [0.2], [joncpl@gmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([pthread], [pthread_create], [], [AC_MSG_ERROR([POSIX thread library is required])])

LIBCURL_CHECK_CONFIG([],[7.32],[],[AC_MSG_ERROR([libcurl is required])])

CPPFLAGS="$CPPFLAGS"
CXXFLAGS="$CXXFLAGS $LIBCURL_CPPFLAGS"
CFLAGS="$CFLAGS $LIBCURL_CPPFLAGS"
LIBS="$LIBS $LIBCURL"

# Checks for header files.
AC_CHECK_HEADERS([ \
	stdio.h \
	stdlib.h \
	stdarg.h \
	time.h \
	string.h 
	])
	
AC_CHECK_HEADER([pthread.h],[AC_DEFINE(PTHREAD_HAVE, [1] ,[ Define to 1 if you have the <pthread.h> header file])])
	
AC_CANONICAL_HOST
ACCRES=""
case "$host_os" in
	mingw*)
	CFLAGS="$CFLAGS -DPTW32_STATIC_LIB -DWINDOWS"
	CPPFLAGS="$CPPFLAGS -DPTW32_STATIC_LIB -DWINDOWS"
	LDFLAGS="$LDFLAGS -static"
	;;
	.*win*.)
	CFLAGS="$CFLAGS -DPTW32_STATIC_LIB -DWINDOWS"
	CPPFLAGS="$CPPFLAGS -DPTW32_STATIC_LIB -DWINDOWS"
	LDFLAGS="$LDFLAGS -static"
	;;
esac
AC_SUBST(ACCRES)

	
#AC_CHECK_HEADERS([sqlite3.h],[],[AC_MSG_ERROR(Could not find sqlite3.h)])
	
# Checks for typedefs, structures, and compiler characteristics.


# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
