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

class Attacks
{
private:
	string move;
	string type;
	int power;
	int accuracy;
	int pp;
	int maxPP;

protected:
	Attacks *next;
	Attacks *prev;

public:
	Attacks();												// default constructor
	Attacks(const char *, const char *, int, int, int = 5); // arg constructor
	Attacks(string, string, int, int, int);					// arg constructor
	virtual ~Attacks();										// destructor

	virtual void display(ostream &) const;					// display data members
	bool compareType(const Attacks &) const;				// compare the type with another object's type
	bool compareType(string) const;							// compare the type with input
	int calcDamage(const float *, const int) const;			// calculate damage
	string mov() const;										// return name for attack
	string typ() const;										// return type for damage calculation
	int pow() const;										// return power for damage calculation
	int acc() const;										// return accuracy for damage calculation
	bool useAttack();										// decrement pp by one to use, return false if pp is 0 for attack
	bool restore();											// restore pp to maxPP
	virtual int useItem() const;							// only for using dynamic binding for function in Items
	friend ostream &operator<<(ostream &, const Attacks &); // overload << operator

	Attacks *&nextLink(); // get next pointer
	Attacks *&prevLink(); // get prev pointer
};

class Items : public Attacks
{
private:
	string name;
	int hp;

public:
	Items();				  // default constructor
	Items(const char *, int); // arg constructor
	Items(string, int);		  // arg constructor
	Items(const Items &);	  // copy constructor
	~Items();				  // destructor

	void display(ostream &) const; // display data members
	int useItem() const;		   // return hp of item for usage
};

#endif
