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
#include "redblacktree.h"

class Kanto
{
private:
	AddOnsDb database;
	RedBlackTree backpack;
	string menu;
	string banner;

	string readBannerFromFile(const char *file); // get banner from text file
	int selectFromMenu();
	bool winSearchLottery();
	void foundPokemon();
	void renamePokemon(Pokemon *&);
	void foundItem();
	Pokemon *drawPokemonType();
	void giveItemToPokemon(Items *item);
	void displayBigAnnouncement(const string = ""); // output an announcement
	void choosePokemonsForBattle(Pokemon *&pokemon1, Pokemon *&pokemon2);
	void battle(Pokemon &pokemon1, Pokemon &pokemon2); // pokemon battle!
	void attack(Pokemon &attacker, Pokemon &defender);
	void declareWinner(Pokemon &pokemon1, Pokemon &pokemon2);

public:
	void init();			 // initialize the game
	void startMenuOptions(); // menu for the whole game
	void searchPokemon();	 // search for pokemon
	void searchItem();		 // search for item
	void battleSimulation(); // pokemon battle!
	void viewPokemon();		 // display all pokemon in backpack
	void trainPokemon();	 // pokemon training
	void healPokemon();		 // heal all pokemon
};

#endif
