#ifndef VMWINDOW_H
#define VMWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/paned.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include "VendingMachine.hpp"
#include "ItemCommunicator.hpp"

class VMWindow : public Gtk::Window , public ItemComm {

public:
  VMWindow(VendingMachine m);
  ~VMWindow();
  double buyItem(double price);
  void insertMoney(double amount);

private:
  Gtk::VPaned *p_top_bottom;
  Gtk::HPaned *p_left_right;
  Gtk::Button *b_coin;
  Gtk::Label  *l_money;
  Gtk::VBox   *bx_buttons;
  Gtk::VBox   *bx_items;
  Gtk::Image  *img_logo;
  double money;
  void insertMoneyButton();
};


#endif //VMWINDOW_H
