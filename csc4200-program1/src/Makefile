all: main

CC = gcc

CXX = g++

LIBS = -lpthread

INCLUDE = -I. -I./except

CFLAGS =

main: exceptions server
	$(CXX) $(INCLUDE) -c main.cxx
	$(CXX) $(INCLUDE) $(LIBS) main.o CServer.o EServer.o -o main

server:
	$(CXX) -c $(INCLUDE) CServer.cxx

exceptions:
	$(CXX) -c $(INCLUDE) except/EServer.cxx

clean:
	rm *.o
	rm main 
