all: main

CC = gcc

CXX = g++

LIBS = -lpthread

INCLUDE = -I. -I./except -I./services

CFLAGS =

main: exceptions server nameserver
	$(CXX) $(INCLUDE) -c main.cxx
	$(CXX) $(INCLUDE) $(LIBS) main.o CServer.o CNameServer.o EServer.o -o main

server: exceptions
	$(CXX) -c $(INCLUDE) CServer.cxx

nameserver: server
	$(CXX) -c $(INCLUDE) services/CNameServer.cxx

exceptions:
	$(CXX) -c $(INCLUDE) except/EServer.cxx

clean:
	rm *.o
	rm main 
