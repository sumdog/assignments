#!/bin/bash
g++ -o main MoneyDialog.cpp ItemButton.cpp main.cpp Item.cpp Soda.cpp SodaMachine.cpp VendingMachine.cpp VMWindow.cpp `pkg-config gtkmm-2.0 --cflags --libs`
