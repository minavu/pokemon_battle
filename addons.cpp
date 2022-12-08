/*
Programmer: Mina Vu
Program:	Pokemon Battle Simulation
File name:  addons.cpp
*/

#include "addons.h"

// default constructor
AddOns::AddOns() : next(0), prev(0) {}

// get next AddOns pointer; return by reference
AddOns *&AddOns::nextLink()
{
	return next;
}

// get previous AddOns pointer; return by reference
AddOns *&AddOns::prevLink()
{
	return prev;
}

// calls AddOns virtual display function
ostream &operator<<(ostream &os, const AddOns &addon)
{
	addon.display(os);
	return os;
}

// insert all Attacks data into ostream
void Attacks::display(ostream &os) const
{
	os << move << ": " << type << ", " << power << " power, " << accuracy << " accuracy, " << pp << " pp";
}

// decrement pp until 0; return 0 or 1
int Attacks::use()
{
	if (pp == 0)
		return 0;

	--pp;
	return 1;
}

// identify type of attack
string Attacks::idType()
{
	return type;
}

// calculates damage to a pokemon; requires pokemon damage factor and pokemon type
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

// set all data for Attacks object
void Attacks::setData(string amove, string atype, int apower, int acc, int amaxPP)
{
	move = amove;
	type = atype;
	power = apower;
	accuracy = acc;
	pp = amaxPP;
	maxPP = amaxPP;
}

// insert all Items data into ostream
void Items::display(ostream &os) const
{
	os << name << ": +" << hp << "hp";
}

// return hp for calculation
int Items::use()
{
	return hp;
}

// identify type as item
string Items::idType()
{
	return "item";
}

// set all data for Items object
void Items::setData(string a_name, int an_hp)
{
	name = a_name;
	hp = an_hp;
}