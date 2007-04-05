VOS - Virtual Operation System
Sumit Khanna
lab #8 / cpsc - 251 / Sumullin

This C++ program expands on the previous program in lab #7. It adds a memory management unit, based on an abstract class with a single implementation. The process has been modified 

Classes:

VOS - Primary operating system that loads scheduler, memory manager and first process
MemoryManagementUnit - Base abstract/pure virtual class for memory management
SimpleMemory - Implementation of MemoryManagementUnit that allocated memory contiguously without using swap. 

To Compile:

From the base directory, type the following:
g++ src/*.cpp -o vos

To Run:
./vos

Sample Output: 
<insert here>

*note, C++ iostream classes are not reentrant so output may be garbled. Running it multiple times will eventually produce this output.  