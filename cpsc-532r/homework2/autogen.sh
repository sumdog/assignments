#!/bin/sh
#autoheader
touch stamp-h
aclocal
autoconf
automake -a
