# Makefile

CC=gcc

PROG=myedit

SRC= src/$(PROG).c src/compile.c

HDR= include/$(PROG).h

CFLAGS= -g
LDFLAGS= -ltcl8.4 -ltk8.4
HDIRS= -Iinclude -I/usr/include/tcl8.4 -I/usr/include/tk8.4

all: $(PROG) $(HDR)

$(HDR):  tcl/$(PROG).tcl
	tcl2str WINSTRING <  tcl/$(PROG).tcl > $(HDR) 

$(PROG): $(SRC) $(HDR)
	$(CC) $(LDFLAGS) $(CFLAGS) $(HDIRS) -o $(PROG) $(SRC)

