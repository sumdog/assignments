all: server client

CXX = g++

CC = gcc

LIBS = -lpthread

INCLUDE = -I. -I./except -I./services

CFLAGS =

server: exceptions cserver nameserver palserver pingserver insults 
	$(CXX) $(INCLUDE) -c main.cxx
	$(CXX) $(INCLUDE) $(LIBS) main.o CPalServer.o CInsultServer.o CPingServer.o CServer.o CNameServer.o ERegister.o EServer.o -o server 

client: clientlib
	$(CC) $(INCLUDE) -c main.c
	$(CC) $(INCLUDE) -o client main.o client.o
clientlib:
	$(CC) $(INCLUDE) -c client.c

cserver: exceptions
	$(CXX) -c $(INCLUDE) CServer.cxx

insults: cserver
	$(CXX) -c $(INCLUDE) services/CInsultServer.cxx

nameserver: cserver
	$(CXX) -c $(INCLUDE) services/CNameServer.cxx

palserver: cserver
	$(CXX) -c $(INCLUDE) services/CPalServer.cxx

pingserver: cserver
	$(CXX) -c $(INCLUDE) services/CPingServer.cxx

exceptions:
	$(CXX) -c $(INCLUDE) except/EServer.cxx
	$(CXX) -c $(INCLUDE) except/ERegister.cxx

clean:
	rm *.o
	rm server
	rm client 
