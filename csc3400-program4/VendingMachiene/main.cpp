#include <gtkmm/main.h>
#include "VMWindow.hpp"
#include "SodaMachine.hpp"

int main(int argc, char *argv[])
{
  
  //create soda machine
  SodaMachine *soda = new SodaMachine();

  //init gtk Graphical User Interface
  Gtk::Main gmain(argc,argv);

  //create primary window
  VMWindow *window = new VMWindow(*soda);

  //run gtk application
  Gtk::Main::run(*window);

  //clean up mess
  delete window;

  //exit
  return 0;

}
