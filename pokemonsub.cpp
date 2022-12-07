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

// = operator overload
Pikachu &Pikachu::operator=(Pikachu &source)
{
	Pokemon::operator=(source);
	return *this;
}

// display pikachu's full information
void Pikachu::displayFullInfo() const
{
	cout << "Your Pikachu's name is: " << name << endl;
	Pokemon::displayFullInfo();
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

// = operator overload
Charmander &Charmander::operator=(Charmander &source)
{
	Pokemon::operator=(source);
	return *this;
}

// display charmander's full info
void Charmander::displayFullInfo() const
{
	cout << "Your Charmander's name is: " << name << endl;
	Pokemon::displayFullInfo();
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

// = operator overload
Squirtle &Squirtle::operator=(Squirtle &source)
{
	Pokemon::operator=(source);
	return *this;
}

// display squirtle's full info
void Squirtle::displayFullInfo() const
{
	cout << "Your Squirtle's name is: " << name << endl;
	Pokemon::displayFullInfo();
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

// = operator overload
Bulbasaur &Bulbasaur::operator=(Bulbasaur &source)
{
	Pokemon::operator=(source);
	return *this;
}

// display bulbasaur's full info
void Bulbasaur::displayFullInfo() const
{
	cout << "Your Bulbasaur's name is: " << name << endl;
	Pokemon::displayFullInfo();
}
