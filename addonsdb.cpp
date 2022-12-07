/*
Programmer: Mina Vu
Assignment: Prog3
File name:  addonsdb.cpp
Class:      CS202
Term:	    Fall 2020

This file contains the implementations for class AddOnsDb.
*/

#include "addonsdb.h"

// default constructor creates a table and initialize everything to 0
AddOnsDb::AddOnsDb() : table(0), size(5)
{
	table = new AddOns* [size];
	for (int i {0}; i < size; ++i)
		table[i] = nullptr;
}

// copy constructor
AddOnsDb::AddOnsDb(const AddOnsDb & source) : table(0), size(source.size)
{
	table = new AddOns* [size];
	for (int i {0}; i < size; ++i)
		copy(table[i], source.table[i]);
}

// destructor
AddOnsDb::~AddOnsDb()
{
	for (int i {0}; i < size; ++i)
		destroy(table[i]);
	delete[] table;
	table = NULL;
}

// recursively copy all of list from source pointer
void AddOnsDb::copy(AddOns* & ptr, AddOns* srcPtr)
{
	ptr = NULL;
	if (srcPtr)
	{
		if (typeid(*srcPtr) == typeid(Items))
		{
			Items *item = dynamic_cast<Items*>(srcPtr);
			ptr = new Items(*item);
		}
		else
		{
			Attacks *attack = dynamic_cast<Attacks*>(srcPtr);
			ptr = new Attacks(*attack);
		}
		copy(ptr->nextLink(), srcPtr->nextLink());
		if (ptr->nextLink())
		{
			ptr->nextLink()->prevLink() = ptr;
		}
	}
}

// recursively destroy all of list from pointer
void AddOnsDb::destroy(AddOns* & ptr)
{
	if (ptr)
	{
		AddOns* temp = ptr;
		ptr = ptr->nextLink();
		delete temp;
		destroy(ptr);
	}
}

bool AddOnsDb::insert(AddOns* addon) {
	for (int i {0}; i < size; ++i) {
		if (!table[i]) {
			return insert(table[i], addon);
		}

		if (table[i]->idType() == addon->idType()) {
			return insert(table[i], addon);
		}
	}

	int oldSize = size;
	size = incrSize();
	return insert(table[oldSize], addon);
}

// recursively insert at end of pointer list
int AddOnsDb::insert(AddOns* & ptr, AddOns* attack)
{
	int done = false;
	if (ptr)
	{
		done = insert(ptr->nextLink(), attack);
		if (done == 1 && ptr->nextLink() == attack)
		{
			ptr->nextLink()->prevLink() = ptr;
			++done;
		}
	}
	else
	{
		ptr = attack;
		++done;
	}
	return done;
}

// display helper function
void AddOnsDb::display()
{
	for (int i {0}; i < size; ++i) {
		cout << "List: " << i + 1 << endl;
		display(table[i]);
		cout << endl;
	}
}

// recursively display all from pointer
void AddOnsDb::display(AddOns* ptr)
{
	if (ptr)
	{
		cout << *ptr << endl;
		display(ptr->nextLink());
	}
}

// increase size of table when more items of different types are added than original table size allowed
int AddOnsDb::incrSize()
{
	int newSize = size + 5;
	AddOns** newTable = new AddOns* [newSize];
	for (int i {0}; i < newSize; ++i)
		newTable[i] = nullptr;

	for (int i {0}; i < size; ++i)
		copy(newTable[i], table[i]);

	for (int i {0}; i < size; ++i)
		destroy(table[i]);
	delete[] table;
	
	table = newTable;
	return newSize;
}

// retrieve an item and return a pointer
// idea is so user retrieving will make copy to add to their table
AddOns* AddOnsDb::retrieve()
{
	int selection = 0;
	bool selected = false;
	for (int i {0}; i < size; ++i) {
		if (table[i]->idType() == "item")
			return retrieve(table[i], selection, selected);
	}
	return nullptr;
}

// retrieve an attack and return a pointer
// random number generator decides what type of attack is chosen
AddOns* AddOnsDb::retrieve(const string & type1, const string type2)
{
	srand(time(NULL));
	int draw = rand() % 3 + 1;
	string type = draw > 1 ? type1 : type2;

	int selection = 0;
	bool selected = false;
	for (int i {0}; i < size; ++i) {
		if (table[i]->idType() == type) 
			return retrieve(table[i], selection, selected);
	}
	return nullptr;
}

// retrieve an attack and return pointer recursion
// rand num gen decides what attack
AddOns* AddOnsDb::retrieve(AddOns* ptr, int &selection, bool &selected, int count)
{
	AddOns* draw = NULL;
	if (ptr)
	{
		draw = retrieve(ptr->nextLink(), selection, selected, ++count);
		if (!selected)
		{
			srand(time(NULL));
			selection = rand() % count + 1;
			selected = true;
		}
		if (count == selection)
		{
			draw = ptr;
		}
	}
	return draw;
}

// add attacks from text file to populate the database
bool AddOnsDb::addAttacks(const char *file)
{
	string string1, string2;
	int a, b, c;
	char buffer[100];

	ifstream myfile(file);
	if (!myfile.is_open())
	{
		cout << "file can't open\n";
		return false;
	}

	while (myfile.peek() != EOF)
	{
		myfile.get(buffer, 100, ',');
		myfile.get();
		string1 = buffer;

		myfile.get(buffer, 100, ',');
		myfile.get();
		string2 = buffer;

		myfile.get(buffer, 100, ',');
		myfile.get();
		a = atoi(buffer);

		myfile.get(buffer, 100, ',');
		myfile.get();
		b = atoi(buffer);

		myfile.get(buffer, 100, ',');
		myfile.get();
		c = atoi(buffer);

		myfile.ignore(100, '\n');

		Attacks* attack = new Attacks();
		attack->setData(string1, string2, a, b, c);
		insert(attack);
	}
	myfile.close();
	return true;
}

// add items from text file to populate database
bool AddOnsDb::addItems(const char* file)
{
	string string1;
	int a;
	char buffer[100];

	ifstream myfile(file);
	if (!myfile.is_open())
	{
		cout << "file can't open\n";
		return false;
	}

	while (myfile.peek() != EOF)
	{
		myfile.get(buffer, 100, ',');
		myfile.get();
		string1 = buffer;

		myfile.get(buffer, 100, ',');
		myfile.get();
		a = atoi(buffer);

		myfile.ignore(100, '\n');

		Items* item = new Items();
		item->setData(string1, a);
		insert(item);
	}
	myfile.close();
	return true;
}
