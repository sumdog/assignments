#!/bin/bash
g++ -o main ItemButton.cpp main.cpp Item.cpp Soda.cpp SodaMachine.cpp VendingMachine.cpp VMWindow.cpp `pkg-config gtkmm-2.0 --cflags --libs`
