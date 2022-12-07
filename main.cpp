/*
Programmer: Mina Vu
Assignment: Prog3
File name:  main.cpp
Class:      CS202
Term:	    Fall 2020

This program is a Pokemon simulation to practice coding with operator overloading, OOP, and dynamic binding.
The Pokemons are sorted into a Red Black balanced tree, and attacks and items are stored in an ARR of DLL.
The text files in the specs folder are needed to have a full experience of this program.
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "kanto.h"

using namespace std;

int main() {
	Kanto kanto;
	kanto.init();
	kanto.startMenuOptions();


	return 0;
}
