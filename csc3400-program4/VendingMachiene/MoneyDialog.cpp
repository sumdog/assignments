#include "MoneyDialog.hpp"
#include <string>
#include <cstring>

/**
 *MoneyDialog() -- constructs a money dialog
 *
 *   dialog so user can input money
 */
MoneyDialog::MoneyDialog(ItemComm *comm) {

  set_modal(true);
  set_title("Enter Price");
  
  com = comm;

  ok = new Gtk::Button("OK");
  text = new Gtk::Entry();
  title = new Gtk::Label("Insert Money");
 
  get_vbox()->pack_start(*title,false,false);
  get_vbox()->pack_start(*text,false,false);

  //setup signal handler
  ok->signal_clicked().connect( SigC::slot(*this, &MoneyDialog::click_ok));

  //set some window prefs
  add_action_widget(*ok,0);
  set_border_width(10);
  set_size_request(200, 150);
  show_all();

}


/**
 *~MoneyDialog() -- destructs the dialog
 *
 *    frees resources allocated by dialog
 */
MoneyDialog::~MoneyDialog() {
  delete ok;
  delete text;
  delete title;
}


/**
 *click_ok()  -- callback function
 *
 *   indicates user has clicked ok on dialog
 *   and adds money to total
 */
void MoneyDialog::click_ok() {
  std::string temp = text->get_text();
  double retval = atol(temp.c_str());
  com->insertMoney(retval);
  hide();
}
