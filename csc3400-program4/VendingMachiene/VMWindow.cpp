#include "VMWindow.hpp"
#include "ItemButton.hpp"
#include "MoneyDialog.hpp"
#include <string>
#include <cstring>

/**
 *VMWindow()  -- constructs primary window
 *
 *PARAMS:     m - vending machine to represent
 *
 *     this is the primary window used for
 *     user ineraction with this application
 */
VMWindow::VMWindow(VendingMachine m) {

  //initalize money
  money = 0;

  //setup components
  p_left_right = new Gtk::HPaned();
  p_top_bottom = new Gtk::VPaned();
  b_coin = new Gtk::Button("Insert Coin");
  l_money = new Gtk::Label("$0.00");
  bx_buttons = new Gtk::VBox(false,1);
  bx_items = new Gtk::VBox(false,1);
  img_logo = new Gtk::Image(m.getImage());

  //Setup window display properities
  set_title("Vending Machiene");
  set_size_request(300,300);

  //set border width
  set_border_width(5);

  //setup first split pane
  add(*p_top_bottom);
  p_left_right->add1(*img_logo);
  p_left_right->add2(*bx_items);

  //setup item buttons
  items_t itm = m.getItems();
  Item **items;
  unsigned long x;
  for(x=0, items=itm.items; x<itm.num_items; x++,items++) {
    VMButton *b = new VMButton((*items)->getName(),**items,this);
    bx_items->pack_start(*b);
  } 

  //setup second pane
  bx_buttons->pack_start(*l_money);
  bx_buttons->pack_start(*b_coin);
  p_top_bottom->add1(*p_left_right);
  p_top_bottom->add2(*bx_buttons);

  //adds signals
  b_coin->signal_clicked().connect( SigC::slot(*this, &VMWindow::insertMoneyButton));

  //show everything
  show_all_children();
}

/**
 *~VMWindow() -- destructs winodow
 *
 *    frees memory allocated to VMWindow
 */
VMWindow::~VMWindow() {

  delete p_top_bottom;
  delete p_left_right;
  delete b_coin;
  delete l_money;
  delete bx_buttons;
  delete img_logo;
}


/**
 *insertMoneyButton() -- bring up money dialog
 */
void VMWindow::insertMoneyButton() {

  MoneyDialog *temp = new MoneyDialog(this);
  temp->run();
  delete temp;

}

/**
 *buyItem() -- callback function for buying item
 *
 *PARMS:       price of item
 *RETURNS:     change or -1 for error
 *
 *     intended as an event handler for item buttons
 */
double VMWindow::buyItem(double price) {
  if(price < money) {
    double temp = money;
    money = 0;
    l_money->set_label("$0.00");
    return temp - price;
  }
  else {
    return -1;
  }
}

/**
 *insertMoney() --callback function for inserting money
 *
 *PARAMS:      amount of money inserted
 */
void VMWindow::insertMoney(double amount) {
  money += amount;
  char mon_tmp[100];
  snprintf(&mon_tmp[0], 100, "$%lf",money);
  string s_temp("");
  s_temp.append(mon_tmp);
  l_money->set_text(s_temp);
}
