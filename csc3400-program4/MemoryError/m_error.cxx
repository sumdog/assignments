/**********************************************
 * Sumit Khanna  --  Program4, CSC3400
 *
 * Memory Error - This program simply
 *  allocates enough memory for the new 
 *  operator to throw an exception
 *********************************************/


#include <string>
#include <exception>
#include <iostream>

int main() {

  //string to grow to fill memory
  std::string *test = new std::string("Bob");

  //infinite loop
  while(1) {
   try{
     //grow string
    (*test) += " Bob ";
   }
   catch(std::exception e) {
     std::cout << "Out of Memory" << std::endl;
     break;
   }
  }//end while

}//end main()
