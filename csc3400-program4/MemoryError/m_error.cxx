#include <string>
#include <exception>
#include <iostream>

int main() {

  std::string *test = new std::string("Bob");

  while(1) {
   try{
    (*test) += " Bob ";
   }
   catch(std::exception e) {
     std::cout << "Out of Memory" << std::endl;
     break;
   }
  }

}
