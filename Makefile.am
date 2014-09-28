AUTOMAKE_OPTIONS = foreign no-dependencies subdir-objects
bin_PROGRAMS = resfix
resfix_SOURCES= src/resfix.cpp \
				src/Log.c src/Log.h \
				src/Exception.hpp
							 
#AM_CPPFLAGS = -Wall

cleanall: distclean
	-rm -rf Makefilee Makefile.in aclocal.m4 autom4te.cache config.h* install-sh missing configure config.guess config.sub
