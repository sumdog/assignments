#ifndef VMWINDOW_H
#define VMWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/paned.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include "VendingMachine.hpp"

class VMWindow : public Gtk::Window {

public:
  VMWindow(VendingMachine m);
  ~VMWindow();

private:
  Gtk::VPaned *p_top_bottom;
  Gtk::HPaned *p_left_right;
  Gtk::Button *b_coin;
  Gtk::Label  *l_money;
  Gtk::VBox   *bx_buttons;
  Gtk::Image  *img_logo;

};


#endif //VMWINDOW_H
