/*
Programmer: Mina Vu
Program:	Pokemon Battle Simulation
File name:  addonsdb.h
*/

#ifndef ADDONSDB_H
#define ADDONSDB_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <string>
#include "addons.h"
#include "minalib.h"

using namespace std;

// AddOnsDB is a data structure using array of doubly-linked lists
class AddOnsDb
{
private:
	AddOns **table;
	int arraySize;

	void copy(AddOns *&, AddOns *);						// copy all table, list recursion
	void destroy(AddOns *&ptr);							// destroy everything, list recursion
	int insert(AddOns *&, AddOns *addon);				// insert item, list recursion
	void display(AddOns *);								// display all, list recursion
	AddOns *retrieve(AddOns *, int &, bool &, int = 0); // retrieve an attack, list recursion

	int expandTable();

public:
	AddOnsDb();
	AddOnsDb(const AddOnsDb &);
	~AddOnsDb();

	bool insert(AddOns *addon);
	void displayAll();
	AddOns *retrieveItem();
	AddOns *retrieveAttack(const string &, const string = "normal");

	bool attacksAddFromFile(const char *);
	bool itemsAddFromFile(const char *);
};

#endif
