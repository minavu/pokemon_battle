/*
Programmer: Mina Vu
Program:	Pokemon Battle Simulation
File name:  addons.h
*/

#ifndef ADDONS_H
#define ADDONS_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <string>
#include "minalib.h"

using namespace std;

// AddOns is an ABC to represent a node in a doubly-linked list
class AddOns
{
protected:
	AddOns *next;
	AddOns *prev;

public:
	AddOns();

	virtual void display(ostream &) const = 0;
	virtual int use() = 0;
	virtual string idType() = 0;

	AddOns *&nextLink();
	AddOns *&prevLink();
	friend ostream &operator<<(ostream &, const AddOns &);
};

// Attacks are used by a Pokemon to fight other Pokemons in battle
class Attacks : public AddOns
{
private:
	string move;
	string type;
	int power;
	int accuracy;
	int pp;
	int maxPP;

public:
	void display(ostream &) const;
	int use();
	string idType();

	void setData(string move, string type, int pow, int acc, int maxPP);
	int calcDamage(const float *, const int) const;
	bool restore();
};

// Items are used by a Pokemon to restore its hp level
class Items : public AddOns
{
private:
	string name;
	int hp;

public:
	void display(ostream &) const;
	int use();
	string idType();

	void setData(string name, int hp);
};

#endif
