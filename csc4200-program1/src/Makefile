all: server client

CXX = g++

CC = gcc

LIBS = -lpthread

INCLUDE = -I. -I./except -I./services

CFLAGS = -g 

server: exceptions cserver nameserver palserver pingserver insults 
	$(CXX) $(CFLAGS) $(INCLUDE) -c main.cxx
	$(CXX) $(CFLAGS) $(INCLUDE) $(LIBS) main.o CPalServer.o CInsultServer.o CPingServer.o CServer.o CNameServer.o ERegister.o EServer.o -o server 

client: clientlib
	$(CC) $(CFLAGS) $(INCLUDE) -c main.c
	$(CC) $(CFLAGS) $(INCLUDE) -o client main.o client.o
clientlib:
	$(CC) $(CFLAGS) $(INCLUDE) -c client.c

cserver: exceptions
	$(CXX) $(CFLAGS) -c $(INCLUDE) CServer.cxx

insults: cserver
	$(CXX) -c $(CFLAGS) $(INCLUDE) services/CInsultServer.cxx

nameserver: cserver
	$(CXX) -c $(CFLAGS) $(INCLUDE) services/CNameServer.cxx

palserver: cserver
	$(CXX) -c $(CFLAGS) $(INCLUDE) services/CPalServer.cxx

pingserver: cserver
	$(CXX) -c $(CFLAGS) $(INCLUDE) services/CPingServer.cxx

exceptions:
	$(CXX) -c $(CFLAGS) $(INCLUDE) except/EServer.cxx
	$(CXX) -c $(CFLAGS) $(INCLUDE) except/ERegister.cxx

clean:
	rm *.o
	rm server
	rm client 
