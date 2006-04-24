#define __STDC_LIMIT_MACROS
#include <stdint.h>

#include <pthread.h>
#include <iostream>
#include "DataSet.hpp"
#include "PipeCommLink.hpp"
#include "SocketCommLink.hpp"
#include "Distribute.hpp"
#include "ForkDistributor.hpp"
#include "ThreadDistributor.hpp"
//#include "Templates.hpp"





int main(int argc, char **argv) {


  //ComLink<int32_t> *com = new PipeComLink<int32_t>();
  ComLink<int32_t> *com = new SocketComLink<int32_t>();
  Distributor<int32_t> *dis = new ForkDistributor<int32_t>(com,20);
  //Distributor<int32_t> *dis = new ThreadDistributor<int32_t>(com,20);
  //split_thread(com);
}
