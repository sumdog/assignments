#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include "DataSet.hpp"
#include "PipeCommLink.hpp"
#include "SocketCommLink.hpp"
//#include "Templates.hpp"

int main(int argc, char **argv) {


  //ComLink<int32_t> *com = new PipeComLink<int32_t>();
  ComLink<int32_t> *com = new SocketComLink<int32_t>();
  if(fork()) {
    com->setSide(PARENT);
    DataSet<int32_t> *ds = new DataSet<int32_t>(INT32_MAX,INT32_MIN,20);
    com->setDataSet(ds);
    com->sendDataSet(11,20);
    //ds->sortSet(0,10);
	//com->recoverSet(11,20);
	ds->printDataSet();
  }
  else {
	sleep(1);
    com->setSide(CHILD);
    com->buildDataSet();
	com->getDataSet()->printDataSet();
    com->getDataSet()->sortSet(0,10);
    com->sendDataSet(0,10);
	 
	  
  }

}
