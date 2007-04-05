/*
 * VOS - Virtual OS / Sumllen's cpsc-251
 *  Sumit Khanna
 */
#ifndef MMU_HPP
#define MMU_HPP
#include <map>
#include <pthread.h>

/*
 * Abstract memory mamnger class to derive memory managers
 */
class MemoryManagerUnit {
  public:
    MemoryManagerUnit(int physical, int swap);
    ~MemoryManagerUnit();
    virtual bool alloc(int proc, char symbol, int size) = 0;
    virtual bool free(int proc, char symbol) = 0;
  protected:
    int physical, swap;
    pthread_mutex_t *memlock;
};

/*
 * Per Process Memory Map
 */
class MemoryMap {
  public:
    MemoryMap();
    MemoryMap(int process);
    ~MemoryMap();
    int getStartSymbol(char c);
    int getEndSymbol(char c);
    void setSymbol(char c, int start, int size);
    void clearSymbol(char c);
    int getProcess();
  private:
    //process id
    int pid;
    //memory location map for symbols
    int *symbolsStart;
    int *symbolsEnd;
};

/*
 * Contigious memory allocator 
 */
class SimpleMemory : public MemoryManagerUnit {
  public:
    SimpleMemory(int physical,int swap);
    ~SimpleMemory();
    virtual bool alloc(int proc, char symbol, int size);
    virtual bool free(int proc, char symbol);    
  private:
    bool *membits;
    bool *swapbits;
    bool allocFirstFreeBlock(int size);
    std::map <int,MemoryMap> mmap;
};





#endif /* MMU_HPP */