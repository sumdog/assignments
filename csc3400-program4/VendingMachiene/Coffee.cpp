/*******************************
 *    Items for Coffee Machine
 *******************************/
#include "Coffee.hpp"
#include <string>

//Coke cost $1.00
Coffee::Coffee() : Item(1.00, std::string("Coffee")) {}

//Sprite cost $1.00
Decaff::Decaff() : Item(1.00, std::string("Decaff")) {}

//Water cost 65 cents
Expresso::Expresso() : Item(2.00, std::string("Expresso")) {}
