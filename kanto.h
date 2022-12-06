/*
Programmer: Mina Vu
Assignment: Prog3
File name:  kanto.h
Class:      CS202
Term:	    Fall 2020

This is the header file for class Kanto.
*/

#ifndef KANTO_H
#define KANTO_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "redblack.h"

class Kanto
{
private:
	AddOnsDb database;
	RedBlack backpack;
	string banner;

	string getBanner(const char* file); // get banner from text file
	int selectFromDisplayedMenu();
	void announce(const string = "");  // output an announcement
	void battle(Pokemon &, Pokemon &); // pokemon battle!

public:
	void init();					// initialize the game
	void start();					// menu for the whole game
	void searchPokemon();			// search for pokemon
	void searchItem();				// search for item
	void battleSim();				// pokemon battle!
	void viewPokemon();				// display all pokemon in backpack
	void trainPokemon();			// pokemon training
	void healPokemon();				// heal all pokemon
};

#endif
