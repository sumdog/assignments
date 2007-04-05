/*
 * VOS - Virtual OS / Sumllen's cpsc-251
 *  Sumit Khanna
 */
#include "mmu.hpp"


MemoryManagerUnit::MemoryManagerUnit(int physical, int swap) : physical(physical), swap(swap) {
  pthread_mutex_init(memlock,NULL);
}

MemoryManagerUnit::~MemoryManagerUnit() {
  pthread_mutex_destroy(memlock);
}

SimpleMemory::SimpleMemory(int physical,int swap) : MemoryManagerUnit(physical,swap) {
  membits = new bool[physical];
  
  for(int i=0; i<physical; i++) {
    membits[i] = false;
  }

}

SimpleMemory::~SimpleMemory() {
  delete[] membits;
}

bool SimpleMemory::alloc(int proc, char symbol, int size) {
  pthread_mutex_lock(memlock);
  
  //no memory map allocated
  if(mmap[proc].getProcess() != -1) {
    mmap[proc] = MemoryMap(proc);
  }
  
  int aloc = allocFirstFreeBlock(size);
  
  //not enought free memory / terminate process
  if(aloc == -1) {
    pthread_mutex_unlock(memlock);
    return false;
  }
  else {
    mmap[proc].setSymbol(symbol, aloc, size);
    pthread_mutex_unlock(memlock);
    return true;
  }
  
}

bool SimpleMemory::free(int proc, char symbol) {
  pthread_mutex_lock(memlock);
  bool err;
  //no memory allocated for process - segmentation fault
  if(mmap[proc].getProcess() == -1) {
    err = false;
  }
  else if(mmap[proc].getStartSymbol(symbol) == 0) {
    //symbol not defined - memory fault
    err = false;
  }
  else {
    mmap[proc].clearSymbol(symbol);
    err = true;
  }
  pthread_mutex_unlock(memlock);
  return err;
}

bool SimpleMemory::allocFirstFreeBlock(int size) {
    int start = -1;
    int counter = 0;
    for(int i=0; i<physical; i++) {
      //find a free block and start counting
      if(membits[i] == false && start == -1) {
        start = i;
        counter++;
      }
      //contine counting on next free block
      else if(membits[i] == false && start != -1) {
        counter++;
        //if we have a large enough block, allocated it and return
        if(counter == size) {
          for(int i = 0; i < counter; i++) {
            membits[start+i] = true;
          }
          return start;
        }
      }
      //end of free block that's not large enough, so reset counter
      else if(membits[i] == true && start != -1) {
        start = -1;
        counter = 0;
      }
    }
    //no contigious blocks free
    return -1;
}

MemoryMap::MemoryMap()  {
  pid = -1;
}

int MemoryMap::getProcess() {
  return pid;
}

MemoryMap::MemoryMap(int process) : pid(process) {
  symbolsStart = new int[sizeof(char)];
  symbolsEnd = new int[sizeof(char)];
  for(int i=0; i<sizeof(char); i++) {
    symbolsStart[i] = 0;
    symbolsEnd[i] = 0;
  }
}

MemoryMap::~MemoryMap() {
  delete[] symbolsStart;
  delete[] symbolsEnd;
}

int MemoryMap::getStartSymbol(char c) {
  return symbolsStart[((int) c)];
}

int MemoryMap::getEndSymbol(char c) {
  return symbolsEnd[((int) c)];
}

void MemoryMap::setSymbol(char c, int start, int size) {
  symbolsStart[((int)c)] = start;
  symbolsEnd[((int)c)] = start+size; 
}

void MemoryMap::clearSymbol(char c) {
  symbolsStart[((int)c)] = 0;
  symbolsEnd[((int)c)] = 0;
}