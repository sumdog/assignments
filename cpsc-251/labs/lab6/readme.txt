VOS - Virtual Operation System
Sumit Khanna
lab #6 / cpsc - 251 / Sumullin

This is a C++ program designed to simulate the scheduling algorithms used by the operating system. For this lab, the program only had one scheduler, and that is a real time scheduler which executes each process, lets them finished completely and then continues to the next process. Future versions of this will expand that scheduler to include more algorithms.

Processes are represented by Text files. The first line of the file contains some basic information about the architecture, memory requirements and registers used. Each following line from the header is one instruction. The instructions are just numbers and are not actually executed. Each instruction takes 1 second to execute. 

Classes:

VOS - Primary operating system that loads scheduler and first process
Process - A class representing a single process which takes in a filename and populates itself accordingly
InitProcess - A subclass of Process which loads all the other processes in a bootstrapping method (not yet implemented)
Scheduler - An abstract class that can be used to create schedulers 
RealTimeScheduler - A Scheduler that executes each process in succession without swapping 

To Compile:

From the base directory, type the following:
g++ src/*.cpp -o vos

To Run:
./vos

