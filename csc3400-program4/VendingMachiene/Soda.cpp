#include "Soda.hpp"
#include <string>

//Coke cost $1.00
Coke::Coke() : Item(1.00, std::string("Coke")) {}

//Sprite cost $1.00
Sprite::Sprite() : Item(1.00, std::string("Sprite")) {}

//Water cost 65 cents
Water::Water() : Item(0.65, std::string("Water")) {}
