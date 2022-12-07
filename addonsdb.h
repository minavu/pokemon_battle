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
	bool insert(AddOns* addon);
	int insert(AddOns* &, AddOns* addon);					  // insert item, list recursion
	void display(AddOns* );							  // display all, list recursion
	AddOns* retrieve(AddOns* , int &, bool &, int = 0); // retrieve an attack, list recursion
	int incrSize();										  // increase size of table array

public:
	AddOnsDb();					// default constructor
	AddOnsDb(const AddOnsDb &); // copy constructor
	~AddOnsDb();				// destructor

	void display();												// display all, helper function
	AddOns* retrieve(const string &, const string = "normal"); // retrieve an attack by type
	AddOns* retrieve();										// retrieve an item

	bool addAttacks(const char *); // populate database with file of attacks
	bool addItems(const char *);   // popluate database with file of items
};

#endif
