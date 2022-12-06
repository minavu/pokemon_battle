/*
Programmer: Mina Vu
Assignment: Prog3
File name:  addonsdb.h
Class:      CS202
Term:	    Fall 2020

This is the header file for the classes AddOnsDb.
AddOnsDb require two .txt files in the specs folder to load attacks and items.
*/

#ifndef ADDONSDB_H
#define ADDONSDB_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <string>
#include "attacks.h"
#include "minalib.h"

using namespace std;

class AddOnsDb
{
private:
	AddOns** table;
	int size;

	void copy(AddOns* &, AddOns*);					  // copy all table, list recursion
	void destroy(AddOns* & ptr);							  // destroy everything, list recursion
	int insert(Attacks *&, Attacks *);					  // insert item, list recursion
	bool insert(Attacks **, Attacks *);					  // insert item, array recursion
	void display(Attacks *);							  // display all, list recursion
	void display(Attacks **, int = 1);					  // display all, array recursion
	Attacks *retrieve(Attacks *, int &, bool &, int = 0); // retrieve an attack, list recursion
	Attacks *retrieve(Attacks **, const string &);		  // retrieve an attack, array recursion
	int incrSize();										  // increase size of table array

public:
	AddOnsDb();					// default constructor
	AddOnsDb(const AddOnsDb &); // copy constructor
	~AddOnsDb();				// destructor

	bool insert(const Attacks &);								// insert attack, helper function
	bool insert(const Items &);									// insert item, helper function
	void display();												// display all, helper function
	Attacks *retrieve(const string &, const string = "normal"); // retrieve an attack by type
	Attacks *retrieve();										// retrieve an item

	bool addAttacks(const char *); // populate database with file of attacks
	bool addItems(const char *);   // popluate database with file of items

	AddOnsDb &operator+=(const Attacks &); //+= operator overload to add an attack
	AddOnsDb &operator+=(const Items &);   //+= operator overload to add an item
};

#endif
