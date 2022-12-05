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

// default constructor
Attacks::Attacks() : move(""), type(""), power(0), accuracy(0), pp(0), maxPP(0), next(0), prev(0) {}

// arg constructor using const char* inputs
Attacks::Attacks(const char *aMove, const char *aType, int pow, int acc, int pp) : move(aMove), type(aType), power(pow), accuracy(acc), pp(pp), maxPP(pp), next(0), prev(0) {}

// arg constructor using string inputs
Attacks::Attacks(string aMove, string aType, int pow, int acc, int pp) : move(aMove), type(aType), power(pow), accuracy(acc), pp(pp), maxPP(pp), next(0), prev(0) {}

// destructor
Attacks::~Attacks() {}

// display function to output the attack info
void Attacks::display(ostream &os) const
{
	os << move << ": " << type << ", " << power << " power, " << accuracy << " accuracy, " << pp << " pp";
}

// compare type of two attacks, return bool
bool Attacks::compareType(const Attacks &that) const
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

// decrease pp or return false if pp is 0
bool Attacks::useAttack()
{
	bool used = false;
	if (pp > 0)
	{
		--pp;
		used = true;
	}
	return used;
}

// restore pp to max pp
bool Attacks::restore()
{
	return pp = maxPP;
}

// required for the hierarchy, no actual body needed for this class
int Attacks::useItem() const
{
	return 0;
}

//<< operator overloading
ostream &operator<<(ostream &os, const Attacks &attack)
{
	attack.display(os);
	return os;
}

// connection to next attack
Attacks *&Attacks::nextLink()
{
	return next;
}

// connection to previous attack
Attacks *&Attacks::prevLink()
{
	return prev;
}

// default constructor
Items::Items() : hp(0) {}

// arg constructor using const char* for input
Items::Items(const char *aName, int hp) : name(aName), hp(hp) {}

// arg constructor using string for input
Items::Items(string aName, int hp) : name(aName), hp(hp) {}

// copy constructor
Items::Items(const Items &source) : Attacks(source), name(source.name), hp(source.hp) {}

// destructor
Items::~Items() {}

// display function to output the item info
void Items::display(ostream &os) const
{
	os << name << ": +" << hp << "hp";
}

// return hp for calculation
int Items::useItem() const
{
	return hp;
}
