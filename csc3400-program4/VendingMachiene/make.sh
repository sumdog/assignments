#!/bin/bash
g++ -o soda MoneyDialog.cpp ItemButton.cpp main.cpp Item.cpp Soda.cpp SodaMachine.cpp VendingMachine.cpp VMWindow.cpp `pkg-config gtkmm-2.0 --cflags --libs`
g++ -o coffee MoneyDialog.cpp ItemButton.cpp main-coffee.cpp Item.cpp Coffee.cpp CoffeeMachine.cpp VendingMachine.cpp VMWindow.cpp `pkg-config gtkmm-2.0 --cflags --libs`
