#ifndef MONEYDIALOG_H
#define MONEYDIALOG_H
#include <gtkmm/dialog.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include "ItemCommunicator.hpp"


class MoneyDialog : public Gtk::Dialog {

public:
  MoneyDialog(ItemComm *comm);
  ~MoneyDialog();

private:
  Gtk::Button *ok;
  Gtk::Entry *text;
  Gtk::Label *title;
  void click_ok();
  ItemComm *com;
} ;



#endif //MONEYDIALOG_H
