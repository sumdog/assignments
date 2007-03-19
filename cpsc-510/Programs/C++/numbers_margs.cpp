/*
 * Sumit Khanna / cpsc-510 / Assignment #5
 *   average number using multiple arguments in C++
 */
#include <iostream>
using std::cout;

int average(int items, ...) {
   
   va_list numbers;
   va_start(numbers,items);
   int avg = 0;
   for(int x=0; x<items;x++) {
     avg += va_arg(numbers,int);
   }
   return ((double)avg) / ((double)items);
}


int main(int argc,char **argv) {
   std::cout << average(10,6,8,12,13,5,7,9,4,13,7); 
   std::cout << std::endl;
}