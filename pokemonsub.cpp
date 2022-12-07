/*
Programmer: Mina Vu
Assignment: Prog3
File name:  pokemonsub.cpp
Class:      CS202
Term:	    Fall 2020

This file contains the implementations for classes Pikachu, Charmander,
Squirtle, and Bulbasaur.
*/

#include "pokemon.h"

// default constructor
Pikachu::Pikachu()
{
	factor = new float[TYPES]{1.0, 2.0, 2.0, 1.0, 1.0};
	type = electric;
	name = "Pikachu";
}

// copy constructor
Pikachu::Pikachu(const Pikachu &source) : Pokemon(source) {}

// display pikachu name
// had more to this before ideas changed
void Pikachu::display(ostream &os) const
{
	os << name;
}

// display pikachu's full information
void Pikachu::displayFullInfo() const
{
	cout << "Your Pikachu's name is: " << name << endl;
	Pokemon::displayFullInfo();
}

// takes damage an attack, use item if holding item, and change status if hp reaches 0
bool Pikachu::hit(const Attacks &attack)
{
	bool hurt = false;
	int damage = attack.calcDamage(factor, type);
	if (damage)
	{
		hp -= damage;
		hurt = true;
	}
	else
	{
		cout << "Hooray! " << name << " dodged the attack!\n";
	}
	if (hp < 100 && hp > 0 && isHoldingItem())
	{
		hp += moves[ITEM]->use();
		cout << name << " used " << *moves[ITEM] << " to increase its hp by a little!\n";
		delete moves[ITEM];
		moves[ITEM] = NULL;
	}
	if (hp <= 0)
	{
		hp = 0;
		status = ko;
	}
	return hurt;
}

//= operator overload
Pikachu &Pikachu::operator=(Pikachu &source)
{
	Pokemon::operator=(source);
	return *this;
}

// default constructor
Charmander::Charmander()
{
	factor = new float[TYPES]{2.0, 1.0, 0.5, 2.5, 1.0};
	type = fire;
	name = "Charmander";
}

// copy constructor
Charmander::Charmander(const Charmander &source) : Pokemon(source) {}

// display charmander's name
void Charmander::display(ostream &os) const
{
	os << name;
}

// display charmander's full info
void Charmander::displayFullInfo() const
{
	cout << "Your Charmander's name is: " << name << endl;
	Pokemon::displayFullInfo();
}

// take damage from an attack, use item if holding, change status if knocked out
bool Charmander::hit(const Attacks &attack)
{
	bool hurt = false;
	int damage = attack.calcDamage(factor, type);
	if (damage)
	{
		hp -= damage;
		hurt = true;
	}
	else
	{
		cout << "Hooray! " << name << " dodged the attack!\n";
	}
	if (hp < 100 && hp > 0 && isHoldingItem())
	{
		hp += moves[ITEM]->use();
		cout << name << " used " << *moves[ITEM] << " to increase its hp by a little!\n";
		delete moves[ITEM];
		moves[ITEM] = NULL;
	}
	if (hp <= 0)
	{
		hp = 0;
		status = ko;
	}
	return hurt;
}

//= operator overload
Charmander &Charmander::operator=(Charmander &source)
{
	Pokemon::operator=(source);
	return *this;
}

// default constructor
Squirtle::Squirtle()
{
	factor = new float[TYPES]{2.0, 2.5, 1.0, 0.5, 1.0};
	type = water;
	name = "Squirtle";
}

// copy constructor
Squirtle::Squirtle(const Squirtle &source) : Pokemon(source) {}

// display squirtle's name
void Squirtle::display(ostream &os) const
{
	os << name;
}

// display full info
void Squirtle::displayFullInfo() const
{
	cout << "Your Squirtle's name is: " << name << endl;
	Pokemon::displayFullInfo();
}

// take damage from an attack
bool Squirtle::hit(const Attacks &attack)
{
	bool hurt = false;
	int damage = attack.calcDamage(factor, type);
	if (damage)
	{
		hp -= damage;
		hurt = true;
	}
	else
	{
		cout << "Hooray! " << name << " dodged the attack!\n";
	}
	if (hp < 100 && hp > 0 && isHoldingItem())
	{
		hp += moves[ITEM]->use();
		cout << name << " used " << *moves[ITEM] << " to increase its hp by a little!\n";
		delete moves[ITEM];
		moves[ITEM] = NULL;
	}
	if (hp <= 0)
	{
		hp = 0;
		status = ko;
	}
	return hurt;
}

//= operator overload
Squirtle &Squirtle::operator=(Squirtle &source)
{
	Pokemon::operator=(source);
	return *this;
}

// default constructor
Bulbasaur::Bulbasaur()
{
	factor = new float[TYPES]{1.0, 0.5, 2.5, 1.0, 1.0};
	type = grass;
	name = "Bulbasaur";
}

// copy construcotr
Bulbasaur::Bulbasaur(const Bulbasaur &source) : Pokemon(source) {}

// display Bulbasaur's name
void Bulbasaur::display(ostream &os) const
{
	os << name;
}

// display full information
void Bulbasaur::displayFullInfo() const
{
	cout << "Your Bulbasaur's name is: " << name << endl;
	Pokemon::displayFullInfo();
}

// take damage from an attack
// these were placed in the derived class because of an early idea that didn't pan out
bool Bulbasaur::hit(const Attacks &attack)
{
	bool hurt = false;
	int damage = attack.calcDamage(factor, type);
	if (damage)
	{
		hp -= damage;
		hurt = true;
	}
	else
	{
		cout << "Hooray! " << name << " dodged the attack!\n";
	}
	if (hp < 100 && hp > 0 && isHoldingItem())
	{
		hp += moves[ITEM]->use();
		cout << name << " used " << *moves[ITEM] << " to increase its hp by a little!\n";
		delete moves[ITEM];
		moves[ITEM] = NULL;
	}
	if (hp <= 0)
	{
		hp = 0;
		status = ko;
	}
	return hurt;
}

//= operator overload
Bulbasaur &Bulbasaur::operator=(Bulbasaur &source)
{
	Pokemon::operator=(source);
	return *this;
}
