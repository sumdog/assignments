#include <gtkmm/main.h>
#include "VMWindow.hpp"
#include "CoffeeMachine.hpp"

int main(int argc, char *argv[])
{
  
  //create coffee machine
  CoffeeMachine *coffee = new CoffeeMachine();

  //init gtk Graphical User Interface
  Gtk::Main gmain(argc,argv);

  //create primary window
  VMWindow *window = new VMWindow(*coffee);

  //run gtk application
  Gtk::Main::run(*window);

  //clean up mess
  delete window;
  delete coffee;

  //exit
  return 0;

}
