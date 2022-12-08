/*
Programmer: Mina Vu
Program:	Pokemon Battle Simulation
File name:  kanto.h
*/

#ifndef KANTO_H
#define KANTO_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "redblacktree.h"

// Region in Pokemon World to catch and train Pokemons
class Kanto
{
private:
	string menu;
	string banner;
	AddOnsDb database;
	RedBlackTree backpack;

	string readBannerFromFile(const char *file);
	int selectFromMenu();
	bool winSearchLottery();
	void foundPokemon();
	void renamePokemon(Pokemon *&);
	void foundItem();
	Pokemon *drawPokemonType();
	void giveItemToPokemon(Items *item);
	void displayBigAnnouncement(const string);
	void choosePokemonsForBattle(Pokemon *&pokemon1, Pokemon *&pokemon2);
	void battle(Pokemon &pokemon1, Pokemon &pokemon2);
	void attack(Pokemon &attacker, Pokemon &defender);
	void declareWinner(Pokemon &pokemon1, Pokemon &pokemon2);

public:
	void initializeGame();
	void gameMenuOptions();
	void searchPokemon();
	void searchItem();
	void trainPokemon();
	void viewPokemon();
	void battleSimulation();
	void healPokemon();
};

#endif
