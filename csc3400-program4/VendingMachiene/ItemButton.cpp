#include "ItemButton.hpp"
#include "Item.hpp"

/**
 *VMButton() - constructs a buttom
 *
 *PARMS:     title of button
 *           item - vending machine item
 *           com - Item Communicator used to 
 *               communicte with main window
 */
VMButton::VMButton(string title, Item item, ItemComm *com) : Gtk::Button(title) {

  //get info from Item
  name = new string(item.getName());
  price = item.getPrice();
  
  //setup callback
  comm = com;
  this->signal_clicked().connect( SigC::slot(*this, &VMButton::b_click) );
}

/**
 *~VMButton() - deconstructs a button
 *
 *   frees memory allocated to button
 */
VMButton::~VMButton() {
  delete name;
}


/**
 *b_click() -- handels a button click
 *
 *   This is a call back function to handel
 *   a user button click
 */
void VMButton::b_click() {  
  
  double change = comm->buyItem(price);

  if( change == -1 ) {
    (Gtk::MessageDialog::MessageDialog("Insufficent Money to Purchase a " + *name)).run();
  }
  else {
    (Gtk::MessageDialog::MessageDialog("Enjoy your " + *name)).run();
  }

} //end b_click()
