#include <string>


int main() {

  std::string *test = new std::string("Bob");

  while(1) {
    (*test) += " Bob ";
  }

}
