VOS - Virtual Operation System
Sumit Khanna
lab #7 / cpsc - 251 / Sumullin

This is a C++ program designed to simulate the scheduling algorithms used by the operating system. This lab expands on the previous lab which had a simple Real Time Scheduler. In this lab, the abstract base class Scheduler is extended to create a Round Robin Scheduler which allots each process the same duration of time to execute. 

Processes are represented by Text files. The first line of the file contains some basic information about the architecture, memory requirements and registers used. Each following line from the header is one instruction. The instructions are just numbers and are not actually executed. Each instruction takes 1 second to execute and the scheduler waits 500ns before swapping out a process. 

Classes:

VOS - Primary operating system that loads scheduler and first process
Process - A class representing a single process which takes in a filename and populates itself accordingly
InitProcess - A subclass of Process which loads all the other processes in a bootstrapping method (not yet implemented)
Scheduler - An abstract class that can be used to create schedulers 
RoundRobinScheduler - A Scheduler that allows each process to run 500ns before swapping it out until all processes are complete

To Compile:

From the base directory, type the following:
g++ src/*.cpp -o vos

To Run:
./vos

Sample Output: 
Executing 1 Cycle of Process "processes/1.proc" -- 11 Operations Left
Executing 1 Cycle of Process "processes/2.proc" -- 5 Operations Left
Executing 1 Cycle of Process "processes/3.proc" -- 12 Operations Left
Executing 1 Cycle of Process "processes/1.proc" -- 10 Operations Left
Executing 1 Cycle of Process "processes/2.proc" -- 4 Operations Left
Executing 1 Cycle of Process "processes/3.proc" -- 11 Operations Left
Executing 1 Cycle of Process "processes/1.proc" -- 9 Operations Left
Executing 1 Cycle of Process "processes/2.proc" -- 3 Operations Left
Executing 1 Cycle of Process "processes/3.proc" -- 10 Operations Left
Executing 1 Cycle of Process "processes/1.proc" -- 8 Operations Left
Executing 1 Cycle of Process "processes/2.proc" -- 2 Operations Left
Executing 1 Cycle of Process "processes/3.proc" -- 9 Operations Left
Executing 1 Cycle of Process "processes/1.proc" -- 7 Operations Left
Executing 1 Cycle of Process "processes/2.proc" -- 1 Operations Left
Executing 1 Cycle of Process "processes/3.proc" -- 8 Operations Left
Executing 1 Cycle of Process "processes/1.proc" -- 6 Operations Left

*note, C++ iostream classes are not reentrant so output may be garbled. Running it multiple times will eventually produce this output.  