/*
Programmer: Mina Vu
Program:	Pokemon Battle Simulation
File name:  addonsdb.cpp
*/

#include "addonsdb.h"

// default constructor
AddOnsDb::AddOnsDb() : table(0), arraySize(5)
{
	table = new AddOns *[arraySize];
	for (int i{0}; i < arraySize; ++i)
		table[i] = nullptr;
}

// copy constructor
AddOnsDb::AddOnsDb(const AddOnsDb &source) : table(0), arraySize(source.arraySize)
{
	table = new AddOns *[arraySize];
	for (int i{0}; i < arraySize; ++i)
		copy(table[i], source.table[i]);
}

// destructor
AddOnsDb::~AddOnsDb()
{
	for (int i{0}; i < arraySize; ++i)
		destroy(table[i]);
	delete[] table;
	table = NULL;
}

// recursively copy all of list from source pointer
void AddOnsDb::copy(AddOns *&ptr, AddOns *srcPtr)
{
	ptr = nullptr;
	if (!srcPtr)
		return;

	if (typeid(*srcPtr) == typeid(Items))
	{
		Items *item = dynamic_cast<Items *>(srcPtr);
		ptr = new Items(*item);
	}
	else
	{
		Attacks *attack = dynamic_cast<Attacks *>(srcPtr);
		ptr = new Attacks(*attack);
	}

	copy(ptr->nextLink(), srcPtr->nextLink());

	if (ptr->nextLink())
		ptr->nextLink()->prevLink() = ptr;
}

// recursively destroy all of list from pointer
void AddOnsDb::destroy(AddOns *&ptr)
{
	if (!ptr)
		return;

	AddOns *temp = ptr;
	ptr = ptr->nextLink();
	delete temp;
	destroy(ptr);
}

// insert AddOns at first open index or in list where type matches;
// expands table if array is filled and types don't match
bool AddOnsDb::insert(AddOns *addon)
{
	for (int i{0}; i < arraySize; ++i)
	{
		if (!table[i])
			return insert(table[i], addon);

		if (table[i]->idType() == addon->idType())
			return insert(table[i], addon);
	}

	int oldSize = arraySize;
	arraySize = expandTable();
	return insert(table[oldSize], addon);
}

// recursively insert AddOns at end of doubly-linked list
int AddOnsDb::insert(AddOns *&ptr, AddOns *addons)
{
	if (!ptr)
	{
		ptr = addons;
		return 1;
	}

	int done = insert(ptr->nextLink(), addons);
	if (done == 1 && ptr->nextLink() == addons)
	{
		ptr->nextLink()->prevLink() = ptr;
		++done;
	}
	return done;
}

// display entire AddOnsDb by list in array
void AddOnsDb::displayAll()
{
	for (int i{0}; i < arraySize; ++i)
	{
		cout << "List: " << i + 1 << endl;
		display(table[i]);
		cout << endl;
	}
}

// recursively display all from list
void AddOnsDb::display(AddOns *ptr)
{
	if (!ptr)
		return;

	cout << *ptr << endl;
	display(ptr->nextLink());
}

// retrieve and return a pointer to an item;
// Pokemon must make a new copy of the item to add to their own data
AddOns *AddOnsDb::retrieveItem()
{
	int selection = 0;
	bool selected = false;
	for (int i{0}; i < arraySize; ++i)
	{
		if (table[i]->idType() == "item")
			return retrieve(table[i], selection, selected);
	}
	return nullptr;
}

// retrieve and return a pointer to an attack with type selected randomly between 2;
// Pokemon must make a new copy of the attack to add to their own data
AddOns *AddOnsDb::retrieveAttack(const string &type1, const string type2)
{
	srand(time(NULL));
	int draw = rand() % 3 + 1;
	string type = draw > 1 ? type1 : type2;

	int selection = 0;
	bool selected = false;
	for (int i{0}; i < arraySize; ++i)
	{
		if (table[i]->idType() == type)
			return retrieve(table[i], selection, selected);
	}
	return nullptr;
}

// recursively retrieve AddOns by randomly selecting from the count of the list
AddOns *AddOnsDb::retrieve(AddOns *ptr, int &selection, bool &selected, int count)
{
	AddOns *draw = NULL;
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

// expand table when more AddOns types are added and table is full
int AddOnsDb::expandTable()
{
	int newSize = arraySize + 5;
	AddOns **newTable = new AddOns *[newSize];
	for (int i{0}; i < newSize; ++i)
		newTable[i] = nullptr;

	for (int i{0}; i < arraySize; ++i)
		copy(newTable[i], table[i]);

	for (int i{0}; i < arraySize; ++i)
		destroy(table[i]);
	delete[] table;

	table = newTable;
	return newSize;
}

// add attacks from text file to populate the database
bool AddOnsDb::attacksAddFromFile(const char *file)
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

		Attacks *attack = new Attacks();
		attack->setData(string1, string2, a, b, c);
		insert(attack);
	}
	myfile.close();
	return true;
}

// add items from text file to populate database
bool AddOnsDb::itemsAddFromFile(const char *file)
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

		Items *item = new Items();
		item->setData(string1, a);
		insert(item);
	}
	myfile.close();
	return true;
}
