/*********************************************
 *Sumit Khanna 
 *  CSC 3400 - Advanced Programming - Rama
 *  Problem #5 
 *
 *  This is a driver program which uses my
 *  stack implementation to determine 
 *  if the word a user inputs is a Palindrome
 *********************************************/

#include "CStack.hpp"
#include "EStack.hpp"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;


int main(int argc, char **argv) {

  //get user input
  string input;
  cout << "Enter a String: " << endl;
  cin >> input;

  
  //extract an array of chars to push on stack
  const char *data = input.data();

  //allocate space for our stack
  CStack *a = new CStack(strlen(data)+1);
  CStack *b = new CStack(strlen(data)+1);

  //fill both stacks
  for(const char *i=data, *j=&data[strlen(data)-1] ;
      *i != '\0' ; i++, j--) {
    
    if( ((short)*i) > 64 && ((short) *i) < 123 ) {
      a->push(*i);
    }
    if( ((short)*j) > 64 && ((short) *j) < 123 ) {
      b->push(*j);
    }
  }

  //check for palindrome
  //and reconstruct string without puncuation
  bool check = true;
  string word("");
  while( ! a->isEmpty() ) {
    char temp = b->pop();
    word += temp;
    if( temp != a->pop() ){
      check = false;
    }
  }

  //return user output
  if(check) {
    cout << word << " is a Palindrome" << endl;
  }
  else {
    cout << word << " is not a Palindrome" << endl;
  }

  //clean up our mess
  delete a,b;
  exit(0);
}
