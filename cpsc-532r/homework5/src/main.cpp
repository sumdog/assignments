#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include "DataSet.hpp"
#include "CommLink.hpp"
//#include "Templates.hpp"

int main(int argc, char **argv) {


  PipeComLink<int32_t> *com = new PipeComLink<int32_t>();
  if(fork()) {
    com->setSide(PARENT);
    DataSet<int32_t> *ds = new DataSet<int32_t>(INT32_MAX,INT32_MIN,20);
    com->setDataSet(ds);
    //ds->printDataSet();
    com->sendDataSet(0,10);
    ds->sortSet(11,20);
    //ds->printDataSet();
  }
  else {
    com->setSide(CHILD);
    //com->setDataSet(ds);
    com->buildDataSet();
    //ds->printDataSet();
    com->getDataSet()->sortSet(0,10);
    com->sandDataSet(0,10);
  }

  //DataSet<int64_t> *a = new DataSet<int64_t>(INT64_MAX,INT64_MIN,10); 
  //a->printDataSet();
}
