#!/bin/sh
rm *.o &> /dev/null
rm main &> /dev/null
gcc listlib.c main.c -o main
gcc -fPIC -c listlib.c
ld -shared -soname liblist.so.1 -o liblist.so.1.0 -lc listlib.o
ln -fs liblist.so.1.0 liblist.so
