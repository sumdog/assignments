all: main

CC = gcc

CXX = g++

LIBS = -lpthread

INCLUDE = -I. -I./except -I./services

CFLAGS =

main: exceptions server nameserver palserver pingserver
	$(CXX) $(INCLUDE) -c main.cxx
	$(CXX) $(INCLUDE) $(LIBS) main.o CPalServer.o CPingServer.o CServer.o CNameServer.o ERegister.o EServer.o -o main

server: exceptions
	$(CXX) -c $(INCLUDE) CServer.cxx

nameserver: server
	$(CXX) -c $(INCLUDE) services/CNameServer.cxx

palserver: server
	$(CXX) -c $(INCLUDE) services/CPalServer.cxx

pingserver: server
	$(CXX) -c $(INCLUDE) services/CPingServer.cxx

exceptions:
	$(CXX) -c $(INCLUDE) except/EServer.cxx
	$(CXX) -c $(INCLUDE) except/ERegister.cxx

clean:
	rm *.o
	rm main 
