all: main

CC = gcc

INCLUDE = .

CFLAGS =

main: problems.o
	$(CC) -I$(INCLUDE) -c main.c
	$(CC) -I$(INCLUDE) main.o problems.o prob1.o prob2.o prob3.o prob5.o prob6.o -o main

problems.o: prob1.o prob2.o prob3.o prob5.o prob6.o 
	$(CC) -I$(INCLUDE) $(CFLAGS) -c problems.c

prob1.o: 
	$(CC) -I$(INCLUDE) $(CFLAGS) -c prob1.c

prob2.o: 
	$(CC) -I$(INCLUDE) $(CFLAGS) -c prob2.c

prob3.o: 
	$(CC) -I$(INCLUDE) $(CFLAGS) -c prob3.c

prob5.o: 
	$(CC) -I$(INCLUDE) $(CFLAGS) -c prob5.c

prob6.o: 
	$(CC) -I$(INCLUDE) $(CFLAGS) -c prob6.c

clean:
	rm *.o
	rm main 
