#include "CServer.h"
#include "except/EServer.h"
#include <iostream>
using std::cout;
#include <errno.h>

int main(int argc, char **argv) {

  CServer *test = new CServer(NULL,8000,20);
  try {
    test->runService();
  }
  catch(EServer e) {
    perror(NULL);
  }
}
