#define __STDC_LIMIT_MACROS
#include <stdint.h>
//#include "DataSet.hpp"
//#include "CommLink.hpp"
#include "Templates.hpp"

int main(int argc, char **argv) {


  DataSet<int32_t> *r = new DataSet<int32_t>(INT32_MAX,INT32_MIN,10);
  r->printDataSet();
  DataSet<int64_t> *a = new DataSet<int64_t>(INT64_MAX,INT64_MIN,10); 
  a->printDataSet();
}
