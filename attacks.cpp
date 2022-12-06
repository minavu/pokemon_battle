/*
Programmer: Mina Vu
Assignment: Prog3
File name:  attacks.cpp
Class:      CS202
Term:	    Fall 2020

This file contains the implementations for classes Attacks and Items.
Some functions were created for an idea that never manifested or changed and therefore
was not used in main program.  Information below for functions.
*/

#include "attacks.h"

AddOns::AddOns() : next(0), prev(0) {}


// connection to next addon
AddOns* & AddOns::nextLink()
{
	return next;
}

// connection to previous addon
AddOns* & AddOns::prevLink()
{
	return prev;
}

// display function to output the attack info
void Attacks::display(ostream & os) const
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

// compare type of two attacks, return bool
bool Attacks::compareType(const Attacks & that) const
{
	return type == that.type;
}

// compare type to input string, return bool
bool Attacks::compareType(string aType) const
{
	return type == aType;
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

// return name for attack
string Attacks::mov() const
{
	return move;
}

// return type for damage calculation
string Attacks::typ() const
{
	return type;
}

// return power for damage calculation
int Attacks::pow() const
{
	return power;
}

// return accuracy for damage calculation
int Attacks::acc() const
{
	return accuracy;
}


// restore pp to max pp
bool Attacks::restore()
{
	return pp = maxPP;
}

//<< operator overloading
ostream &operator<<(ostream & os, const Attacks & attack)
{
	attack.display(os);
	return os;
}


// display function to output the item info
void Items::display(ostream & os) const
{
	os << name << ": +" << hp << "hp";
}

// return hp for calculation
int Items::use()
{
	return hp;
}
