/*
Programmer: Mina Vu
Assignment: Prog3
File name:  addons.h
Class:      CS202
Term:	    Fall 2020

This is the header file for the classes Attacks and Items.
Items class is derived from Attacks class simply for dynamic binding in AddOnsDb.
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

	AddOns *&nextLink();								   // get next pointer
	AddOns *&prevLink();								   // get prev pointer
	friend ostream &operator<<(ostream &, const AddOns &); // overload << operator
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
	void display(ostream &) const; // display data members
	int use();					   // decrement pp by one to use, return false if pp is 0 for attack
	string idType();

	void setData(string move, string type, int pow, int acc, int maxPP);
	int calcDamage(const float *, const int) const; // calculate damage
	bool restore();									// restore pp to maxPP
};

class Items : public AddOns
{
private:
	string name;
	int hp;

public:
	void display(ostream &) const; // display data members
	int use();					   // return hp of item for usage
	string idType();

	void setData(string name, int hp);
};

#endif