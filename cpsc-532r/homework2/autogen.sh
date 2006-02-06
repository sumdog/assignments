#!/bin/sh
#autoheader
touch stamp-h
aclocal
autoconf
touch NEWS README AUTHORS ChangeLog
automake -a
