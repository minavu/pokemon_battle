/*
Programmer: Mina Vu
Assignment: Prog3
File name:  addons.cpp
Class:      CS202
Term:	    Fall 2020

This file contains the implementations for classes Attacks and Items.
Some functions were created for an idea that never manifested or changed and therefore
was not used in main program.  Information below for functions.
*/

#include "addons.h"

AddOns::AddOns() : next(0), prev(0) {}

// connection to next addon
AddOns *&AddOns::nextLink()
{
	return next;
}

// connection to previous addon
AddOns *&AddOns::prevLink()
{
	return prev;
}

//<< operator overloading
ostream &operator<<(ostream &os, const AddOns &addon)
{
	addon.display(os);
	return os;
}

// display function to output the attack info
void Attacks::display(ostream &os) const
{
	os << move << ": " << type << ", " << power << " power, " << accuracy << " accuracy, " << pp << " pp";
}

// decrease pp, return pp used
int Attacks::use()
{
	if (pp == 0)
		return 0;

	--pp;
	return 1;
}

string Attacks::idType()
{
	return type;
}

// calculate damage an attack deals to the pokemon, requires pokemon damage factor and type
int Attacks::calcDamage(const float *factor, const int index) const
{
	int damage = 0;
	int hit = 1;
	if (accuracy != 100)
	{
		srand(time(NULL));
		hit = rand() % (accuracy / 10);
	}
	if (hit)
	{
		damage = factor[index] * power;
	}
	return damage;
}

// restore pp to max pp
bool Attacks::restore()
{
	return pp = maxPP;
}

void Attacks::setData(string amove, string atype, int apower, int acc, int amaxPP)
{
	move = amove;
	type = atype;
	power = apower;
	accuracy = acc;
	pp = amaxPP;
	maxPP = amaxPP;
}

// display function to output the item info
void Items::display(ostream &os) const
{
	os << name << ": +" << hp << "hp";
}

// return hp for calculation
int Items::use()
{
	return hp;
}

string Items::idType()
{
	return "item";
}

void Items::setData(string a_name, int an_hp)
{
	name = a_name;
	hp = an_hp;
}