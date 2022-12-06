/*
Programmer: Mina Vu
Assignment: Prog3
File name:  attacks.h
Class:      CS202
Term:	    Fall 2020

This is the header file for the classes Attacks and Items.
Items class is derived from Attacks class simply for dynamic binding in AddOnsDb.
*/

#ifndef ATTACKS_H
#define ATTACKS_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <string>
#include "minalib.h"

using namespace std;

class AddOns {
	protected:
		AddOns* next;
		AddOns* prev;

	public:
		AddOns();
		virtual void display(ostream &) const = 0;
		virtual int use() = 0;
		AddOns* & nextLink();	// get next pointer
		AddOns* & prevLink();	// get prev pointer
};

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
	void display(ostream &) const;					// display data members
	int use();										// decrement pp by one to use, return false if pp is 0 for attack
	bool compareType(const Attacks &) const;				// compare the type with another object's type
	bool compareType(string) const;							// compare the type with input
	int calcDamage(const float *, const int) const;			// calculate damage
	string mov() const;										// return name for attack
	string typ() const;										// return type for damage calculation
	int pow() const;										// return power for damage calculation
	int acc() const;										// return accuracy for damage calculation
	bool restore();											// restore pp to maxPP
	friend ostream &operator<<(ostream &, const Attacks &); // overload << operator
};

class Items : public AddOns
{
private:
	string name;
	int hp;

public:
	void display(ostream &) const; // display data members
	int use();		   // return hp of item for usage
};

#endif
