#include <gtkmm/main.h>
#include "VMWindow.hpp"

int main(int argc, char *argv[])
{
  /*
  initscr();
  
  WINDOW *vend = newwin(10,20,5,5);
  mvwprintw(vend, 2, 2, "%s", "Hello World");
  wrefresh(vend);
  sleep(2);
   refresh();
   //getch();
   sleep(2);
   endwin();

   return 0;
  */
  
  Gtk::Main gmain(argc,argv);

  VMWindow *window = new VMWindow();

  Gtk::Main::run(*window);

  delete window;

  return 0;

}
