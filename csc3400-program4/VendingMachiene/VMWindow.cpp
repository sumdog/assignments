#include "VMWindow.hpp"

VMWindow::VMWindow() {

  //setup components
  p_left_right = new Gtk::HPaned();
  p_top_bottom = new Gtk::VPaned();
  b_coin = new Gtk::Button("Insert Coin");
  l_money = new Gtk::Label("$0.00");
  bx_buttons = new Gtk::VBox(false,1);
  img_logo = new Gtk::Image("default.jpg");

  //Setup window display properities
  set_title("Vending Machiene");
  set_size_request(300,300);

  //set border width
  set_border_width(5);

  //setup first split pane
  add(*p_top_bottom);
  p_left_right->add1(*p_left_right);

  //setup second pane
  bx_buttons->pack_start(*l_money);
  bx_buttons->pack_start(*b_coin);
  p_top_bottom->add1(*img_logo);
  p_top_bottom->add2(*bx_buttons);

 
  //show everything
  show_all_children();
}

VMWindow::~VMWindow() {

  delete p_top_bottom;
  delete p_left_right;
  delete b_coin;
  delete l_money;
  delete bx_buttons;
  delete img_logo;
}
