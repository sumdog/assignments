#ifndef ITEMBUTTON_H
#define ITEMBUTTON_H
#include <gtkmm/button.h>
#include <gtkmm/messagedialog.h>
#include "Item.hpp"
#include "ItemCommunicator.hpp"
#include <string>
using std::string;

class VMButton : public Gtk::Button {

public:
  VMButton(string title, Item item, ItemComm *com);
  ~VMButton();

private:
  void b_click();
  string *name;
  double price;
  ItemComm *comm;

};

#endif //ITEMBUTTON_H
