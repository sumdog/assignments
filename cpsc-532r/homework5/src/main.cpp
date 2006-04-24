#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <time.h>
#include <pthread.h>
#include <iostream>
#include "DataSet.hpp"
#include "PipeCommLink.hpp"
#include "SocketCommLink.hpp"
#include "Distribute.hpp"
#include "ForkDistributor.hpp"
#include "ThreadDistributor.hpp"
//#include "Templates.hpp"


void usage() {
  cout << "\ncpsc532r-hw5 <setsize> [32|64] [single|forkpipe|forksock|threadpipe] \n\n";
  exit(1);
}


int main(int argc, char **argv) {

  if(argc != 4) {
   usage();
  }

  int setsize = strtoul(argv[1],NULL,0);
  int bitsize = atol(argv[2]);
  char *type = argv[3];

  /*
   *in a single proc, we'll have one dataset 
   *of the total size. Otherwise, we'll have
   *two datasets, i.e setsize/2
   */
  if(!strcmp(type,"single")) {
    setsize = setsize/2;
  }

  /* all the variables we need */
  ComLink<int32_t> *com32;
  Distributor<int32_t> *dis32;
  DataSet<int32_t> *data32;
  ComLink<int64_t> *com64;
  Distributor<int64_t> *dis64;
  DataSet<int64_t> *data64;
  char *filename;
  time_t start,end;

  if(bitsize == 32) {
    /* --- 32-bit --- */
    if(strcmp(type,"single")) {
      filename = "/tmp/single_32.out";
      cout << "Process: Single\tComm: NA\tInt: 32bit\tFile: " << filename << "\n" << std::flush;
      data32 = new DataSet<int32_t>(INT32_MAX,INT32_MIN,setsize);
      start = time(0);
      data32->sortSet();
      end = time(0);
      cout << "Time Elapsed(single):" << end-start << " sec\n" <<std::flush;
      data32->printDataSet(filename);
    }
    else if(strcmp(type,"forkpipe")) {
      filename = "/tmp/forkpipe_32.out";
      cout << "Process: Fork\tComm: Pipe\tInt: 32bits\tFile: " << filename << "\n" << std::flush;
      com32 = new PipeComLink<int32_t>();
      dis32 = new ForkDistributor<int32_t>(com32,setsize,filename);
    }
    else if(strcmp(type,"forksock")) {
    
      filename = "/tmp/forksock_32.out";
      cout << "Process: Fork\tComm: Sock\tInt: 32bits\tFile: " << filename << "\n" << std::flush;
      com32 = new SocketComLink<int32_t>();
      dis32 = new ForkDistributor<int32_t>(com32,setsize,filename);
    }
    else if(strcmp(type,"threadpipe")) {
      filename = "/tmp/threadpipe_32.out";
      cout << "Process: Thread\tComm: Pipe\tInt: 32bits\tFile: " << filename << "\n" << std::flush;
      com32 = new PipeComLink<int32_t>();
      dis32 = new ThreadDistributor<int32_t>(com32,setsize,filename);
    }
    else {
      usage();
    }
  }
  else if (bitsize == 64) {
    
    /* --- 64-bit --- */
    if(strcmp(type,"single")) {

      filename = "/tmp/single_64.out";
      cout << "Process: Single\tComm: NA\tInt: 64bit\tFile: " << filename << "\n" << std::flush;
      data64 = new DataSet<int64_t>(INT64_MAX,INT64_MIN,setsize);
      start = time(0);
      data64->sortSet();
      end = time(0);
      cout << "Time Elapsed(single):" << end-start << " sec\n" << std::flush;
      data64->printDataSet(filename);
    }
    else if(strcmp(type,"forkpipe")) {
      filename = "/tmp/forkpipe_64.out";
      cout << "Process: Fork\tComm: Pipe\tInt: 64bits\tFile: " << filename << "\n";
      com64 = new PipeComLink<int64_t>();
      dis64 = new ForkDistributor<int64_t>(com64,setsize,filename);
    }
    else if(strcmp(type,"forksock")) {
      
      filename = "/tmp/forksock_64.out";
      cout << "Process: Fork\tComm: Sock\tInt: 64bits\tFile: " << filename << "\n" << std::flush;
      com64 = new SocketComLink<int64_t>();
      dis64 = new ForkDistributor<int64_t>(com64,setsize,filename);
    }
    else if(strcmp(type,"threadpipe")) {
      filename = "/tmp/threadpipe_64.out";
      cout << "Process: Thread\tComm: Pipe\tInt: 64bits\tFile: " << filename << "\n" << std::flush;
      com64 = new PipeComLink<int64_t>();
      dis64 = new ThreadDistributor<int64_t>(com64,setsize,filename);
    }
    else {
      usage();
    }
  }
  else {
    usage();
  }
    

  //ComLink<int32_t> *com = new PipeComLink<int32_t>();
  //ComLink<int32_t> *com = new SocketComLink<int32_t>();
  //Distributor<int32_t> *dis = new ForkDistributor<int32_t>(com,20);
  //Distributor<int32_t> *dis = new ThreadDistributor<int32_t>(com,20);
  //split_thread(com);
}
