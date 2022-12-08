/*
Programmer: Mina Vu
Program:	Pokemon Battle Simulation
File name:  pokemonsub.h
*/

#ifndef POKEMONSUB_H
#define POKEMONSUB_H

#include <iostream>
#include "pokemonabc.h"

using namespace std;

// Electric type Pokemon
class Pikachu : public Pokemon
{
public:
	Pikachu();
	Pikachu(const Pikachu &);
	Pikachu &operator=(Pikachu &);

	void displayFullInfo() const;
};

// Fire type Pokemon
class Charmander : public Pokemon
{
public:
	Charmander();
	Charmander(const Charmander &);
	Charmander &operator=(Charmander &);

	void displayFullInfo() const;
};

// Water type Pokemon
class Squirtle : public Pokemon
{
public:
	Squirtle();
	Squirtle(const Squirtle &);
	Squirtle &operator=(Squirtle &);

	void displayFullInfo() const;
};

// Grass type Pokemon
class Bulbasaur : public Pokemon
{
public:
	Bulbasaur();
	Bulbasaur(const Bulbasaur &);
	Bulbasaur &operator=(Bulbasaur &);

	void displayFullInfo() const;
};

#endif
