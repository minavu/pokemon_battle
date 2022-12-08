/*
Programmer: Mina Vu
Assignment: Prog3
File name:  pokemonsub.h
Class:      CS202
Term:	    Fall 2020

This is the header file for abstract base class Pokemon and its derived classes
Pikachu, Charmander, Squirtle, and Bulbasaur.  Each Pokemon derived classes takes
a pointer to the attacks/items database to populate their moves set.
*/

#ifndef POKEMONSUB_H
#define POKEMONSUB_H

#include <iostream>
#include "pokemonabc.h"

using namespace std;

class Pikachu : public Pokemon
{
public:
	Pikachu();										  // default constructor
	Pikachu(const Pikachu &);						  // copy constructor
	Pikachu &operator=(Pikachu &); // overload = operator

	void displayFullInfo() const;  // display all info
};

class Charmander : public Pokemon
{
public:
	Charmander();											// default constructor
	Charmander(const Charmander &);							// copy constructor
	Charmander &operator=(Charmander &); // overload = operator

	void displayFullInfo() const;  // display all info
};

class Squirtle : public Pokemon
{
public:
	Squirtle();											// default constructor
	Squirtle(const Squirtle &);							// copy constructor
	Squirtle &operator=(Squirtle &); // overload = operator

	void displayFullInfo() const;  // display all info
};

class Bulbasaur : public Pokemon
{
public:
	Bulbasaur();										  // default constructor
	Bulbasaur(const Bulbasaur &);						  // copy constructor
	Bulbasaur &operator=(Bulbasaur &); // overload = operator

	void displayFullInfo() const;  // display all info
};

#endif
