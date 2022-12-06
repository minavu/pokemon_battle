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
		table[i] {nullptr};
}

// copy constructor
AddOnsDb::AddOnsDb(const AddOnsDb & source) : table(0), size(source.size)
{
	table = new AddOns* [size];
	for (int i {0}; i < size; ++i)
		copy(table[i], source[i]);
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

// insert helper function for an attack
bool AddOnsDb::insert(const Attacks &attack)
{
	Attacks *add = new Attacks(attack);
	bool done = insert(table, add);
	if (!done)
	{
		size = incrSize();
		done = insert(table, add);
	}
	return done;
}

// insert helper function for an item
bool AddOnsDb::insert(const Items &item)
{
	Attacks *add = new Items(item);
	bool done = insert(table, add);
	if (!done)
	{
		size = incrSize();
		done = insert(table, add);
	}
	return done;
}

// recursively insert at end of pointer
int AddOnsDb::insert(Attacks *&ptr, Attacks *attack)
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

// recursively insert into table were type matches
bool AddOnsDb::insert(Attacks **arr, Attacks *attack)
{
	bool done = false;
	if (arr != table + size)
	{
		if (*arr == NULL)
		{
			done = insert(*arr, attack);
		}
		else
		{
			if ((*arr)->compareType(*attack))
			{
				done = insert(*arr, attack);
			}
			else
			{
				done = insert(++arr, attack);
			}
		}
	}
	return done;
}

// display helper function
void AddOnsDb::display()
{
	display(table);
}

// recursively display all from pointer
void AddOnsDb::display(Attacks *ptr)
{
	if (ptr)
	{
		cout << *ptr << endl;
		display(ptr->nextLink());
	}
}

// recursively display all from table
void AddOnsDb::display(Attacks **arr, int count)
{
	if (arr != table + size)
	{
		cout << "List: " << count << endl;
		display(*arr);
		cout << endl;
		display(++arr, ++count);
	}
}

// increase size of table when more items of different types are added than original table size allowed
int AddOnsDb::incrSize()
{
	int newSize = size + 5;
	Attacks **newTable = new Attacks *[newSize];
	init(newTable, newTable, newSize);
	copy(newTable, newTable, table);
	destroy(table);
	delete[] table;
	table = newTable;
	return newSize;
}

// retrieve an item and return a pointer
// idea is so user retrieving will make copy to add to their table
Attacks *AddOnsDb::retrieve()
{
	return retrieve(table, "");
}

// retrieve an attack and return a pointer
// random number generator decides what type of attack is chosen
Attacks *AddOnsDb::retrieve(const string &type1, const string type2)
{
	srand(time(NULL));
	int draw = rand() % 3 + 1;
	Attacks *temp = NULL;
	if (draw > 1)
	{
		temp = retrieve(table, type1);
	}
	else
	{
		temp = retrieve(table, type2);
	}
	return temp;
}

// retrieve an attack and return pointer recursion
// rand num gen decides what attack
Attacks *AddOnsDb::retrieve(Attacks *ptr, int &selection, bool &selected, int count)
{
	Attacks *draw = NULL;
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

// retrieve an attack and return pointer array recursion
Attacks *AddOnsDb::retrieve(Attacks **arr, const string &type)
{
	int selection = 0;
	bool selected = false;
	Attacks *draw = NULL;
	if (arr != table + size)
	{
		if (*arr && (*arr)->compareType(type))
		{
			draw = retrieve(*arr, selection, selected);
		}
		else
		{
			draw = retrieve(++arr, type);
		}
	}
	return draw;
}

// add attacks from text file to populate the database
bool AddOnsDb::addAttacks(const char *file)
{
	bool done = true;
	string string1, string2;
	int a, b, c;
	char buffer[100];

	ifstream myfile(file);
	if (myfile.is_open())
	{
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

			Attacks attack(string1, string2, a, b, c);
			*this += attack;
			// insert(attack);
		}
	}
	else
	{
		cout << "file can't open\n";
		done = false;
	}
	myfile.close();
	return done;
}

// add items from text file to populate database
bool AddOnsDb::addItems(const char *file)
{
	bool done = true;
	string string1;
	int a;
	char buffer[100];

	ifstream myfile(file);
	if (myfile.is_open())
	{
		while (myfile.peek() != EOF)
		{
			myfile.get(buffer, 100, ',');
			myfile.get();
			string1 = buffer;

			myfile.get(buffer, 100, ',');
			myfile.get();
			a = atoi(buffer);

			myfile.ignore(100, '\n');

			Items item(string1, a);
			*this += item;
			// insert(item);
		}
	}
	else
	{
		cout << "file can't open\n";
		done = false;
	}
	myfile.close();
	return done;
}

//+= operator overload
AddOnsDb &AddOnsDb::operator+=(const Attacks &attack)
{
	insert(attack);
	return *this;
}

//+= operator overload
AddOnsDb &AddOnsDb::operator+=(const Items &item)
{
	insert(item);
	return *this;
}
