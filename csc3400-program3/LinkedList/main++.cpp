#include "listlib++.hpp"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
using std::cout;
using std::cin;
using std::endl;

int main() {
  
  //check to see if we're in interactive mode
  int tty = isatty(fileno(stdin));

  //prompt user
  if(tty) {
    cout << "Linked List (C++) -- Interactive Mode" << endl;
    cout << "Enter a list, one integer per line" << endl;
    cout << "Exit with ^D" << endl;
    cout << ">>>";
  }

  //setup list
  CLinkList *list = new CLinkList();

  //read user input
  while(!cin.eof()) {
    long in;
    cin >> in;
    list->addElement((atom_t) in);
    if(tty) { cout << ">>>"; }
  }

  //display list
  

}
