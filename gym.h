/*
Programmer: Mina Vu
Assignment: Prog3
File name:  gym.h
Class:      CS202
Term:	    Fall 2020

This is the header file for classes Gym and Kanto.
Gym class was created first aligning with the original design but could've been combined with Kanto class.
*/

#ifndef GYM_H
#define GYM_H

#include "redblack.h"

class Gym
{
private:
	string announcement;

public:
	Gym(); // default constructor

	void announce(const string = "");  // output an announcement
	void battle(Pokemon &, Pokemon &); // pokemon battle!
};

class Kanto
{
private:
	AddOnsDb database;
	Gym gym;
	RedBlack backpack;
	string banner;

public:
	Kanto();  // default constructor
	~Kanto(); // destructor

	void init();					// initialize the game
	void start();					// menu for the whole game
	string getBanner(const char *); // get banner from text file
	Pokemon *create(int);			// create a pokemon by type indication
	string type(Pokemon *);			// return type of pokemon as string
	void searchPokemon();			// search for pokemon
	void searchItem();				// search for item
	void battleSim();				// pokemon battle!
	void viewPokemon();				// display all pokemon in backpack
	void trainPokemon();			// pokemon training
	void healPokemon();				// heal all pokemon
};

#endif
