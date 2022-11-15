/*
Programmer: Mina Vu
Assignment: Prog3
File name:  attacks.cpp
Class:      CS202
Term:	    Fall 2020

This file contains the implementations for classes Attacks, Items, and AddOnsDb.
Some functions were created for an idea that never manifested or changed and therefore
was not used in main program.  Information below for functions.
*/

#include "attacks.h"

//default constructor
Attacks::Attacks() : move(""), type(""), power(0), accuracy(0), pp(0), maxPP(0), next(0), prev(0) {}

//arg constructor using const char* inputs
Attacks::Attacks(const char* aMove, const char* aType, int pow, int acc, int pp) : move(aMove), type(aType), power(pow), accuracy(acc), pp(pp), maxPP(pp), next(0), prev(0) {}

//arg constructor using mstr inputs
Attacks::Attacks(mstr aMove, mstr aType, int pow, int acc, int pp) : move(aMove), type(aType), power(pow), accuracy(acc), pp(pp), maxPP(pp), next(0), prev(0) {}

//destructor
Attacks::~Attacks() {}

//display function to output the attack info
void Attacks::display(ostream & os) const {
	os << move << ": " << type << ", " << power << " power, " << accuracy << " accuracy, " << pp << " pp";
}

//compare type of two attacks, return bool
bool Attacks::compareType(const Attacks & that) const {
	return type == that.type;
}

//compare type to input string, return bool
bool Attacks::compareType(mstr aType) const {
	return type == aType;
}

//calculate damage an attack deals to the pokemon, requires pokemon damage factor and type
int Attacks::calcDamage(const float* factor, const int index) const {
	int damage = 0;
	int hit = 1;
	if (accuracy != 100) {
		srand(time(NULL));
		hit = rand() % (accuracy / 10);
	}
	if (hit) {
		damage = factor[index] * power;
	}
	return damage;
}

//return name for attack
mstr Attacks::mov() const {
	return move;
}

//return type for damage calculation
mstr Attacks::typ() const {
	return type;
}

//return power for damage calculation
int Attacks::pow() const {
	return power;
}

//return accuracy for damage calculation
int Attacks::acc() const {
	return accuracy;
}

//decrease pp or return false if pp is 0
bool Attacks::useAttack() {
	bool used = false;
	if (pp > 0) {
		--pp;
		used = true;
	}
	return used;
}

//restore pp to max pp
bool Attacks::restore() {
	return pp = maxPP;
}

//required for the hierarchy, no actual body needed for this class
int Attacks::useItem() const {
	return 0;
}

//<< operator overloading
ostream & operator<< (ostream & os, const Attacks & attack) {
	attack.display(os);
	return os;
}

//connection to next attack
Attacks* & Attacks::nextLink() {
	return next;
}

//connection to previous attack
Attacks* & Attacks::prevLink() {
	return prev;
}









//default constructor
Items::Items() : hp(0) {}

//arg constructor using const char* for input
Items::Items(const char* aName, int hp) : name(aName), hp(hp) {}

//arg constructor using mstr for input
Items::Items(mstr aName, int hp) : name(aName), hp(hp) {}

//copy constructor
Items::Items(const Items & source) : Attacks(source), name(source.name), hp(source.hp) {}

//destructor
Items::~Items() {}

//display function to output the item info
void Items::display(ostream & os) const {
	os << name << ": +" << hp << "hp";
}

//return hp for calculation
int Items::useItem() const {
	return hp;
}









//default constructor creates a table and initialize everything to 0
AddOnsDb::AddOnsDb() : table(0), size(5) {//change back to 5 after figure out copy messup in incrSize function
	table = new Attacks*[size];
	init(table, table, size);
}

//copy constructor
AddOnsDb::AddOnsDb(const AddOnsDb & source) : table(0), size(source.size) {
	table = new Attacks*[size];
	copy(table, table, source.table);
}

//destructor
AddOnsDb::~AddOnsDb() {
	destroy(table);
	delete [] table;
	table = NULL;
}

//recursively initialize each array index to 0, can be used with any table not just this object
void AddOnsDb::init(Attacks** arr, Attacks** tbl, int s) {
	if (arr != tbl + s) {
		*arr = NULL;
		init(++arr, tbl, s);
	}
} 

//recursively copy all from source pointer
void AddOnsDb::copy(Attacks* & ptr, Attacks* srcPtr) {
	ptr = NULL;
	if (srcPtr) {
		if (typeid(*srcPtr) == typeid(Items)) {
			Items* item = dynamic_cast<Items*>(srcPtr);
			ptr = new Items(*item);
		} else {
			ptr = new Attacks(*srcPtr);
		}
		copy(ptr->nextLink(), srcPtr->nextLink());
		if (ptr->nextLink()) {
			ptr->nextLink()->prevLink() = ptr;
		}
	}
}

//recursively copy all from source table
void AddOnsDb::copy(Attacks** arr, Attacks** dstTbl, Attacks** srcTbl) {
	if (arr != dstTbl + size) {
		copy(*arr, *srcTbl);
		copy(++arr, dstTbl, ++srcTbl);
	}
}

//recursively destroy all from pointer
void AddOnsDb::destroy(Attacks* & ptr) {
	if (ptr) {
		Attacks* temp = ptr;
		ptr = ptr->nextLink();
		delete temp;
		destroy(ptr);
	}
}

//recursively destroy all from table
void AddOnsDb::destroy(Attacks** arr) {
	if (arr != table + size) {
		destroy(*arr);
		destroy(++arr);
	}
}

//insert helper function for an attack
bool AddOnsDb::insert(const Attacks & attack) {
	Attacks* add = new Attacks(attack);
	bool done = insert(table, add);
	if (!done) {
		size = incrSize();
		done = insert(table, add);
	}
	return done;
}

//insert helper function for an item
bool AddOnsDb::insert(const Items & item) {
	Attacks* add = new Items(item);
	bool done = insert(table, add);
	if (!done) {
		size = incrSize();
		done = insert(table, add);
	}
	return done;
}

//recursively insert at end of pointer
int AddOnsDb::insert(Attacks* & ptr, Attacks* attack) {
	int done = false;
	if (ptr) {
		done = insert(ptr->nextLink(), attack);
		if (done == 1 && ptr->nextLink() == attack) {
			ptr->nextLink()->prevLink() = ptr;
			++done;
		}
	} else {
		ptr = attack;
		++done;
	}	
	return done;
}

//recursively insert into table were type matches
bool AddOnsDb::insert(Attacks** arr, Attacks* attack) {
	bool done = false;
	if (arr != table + size) {
		if (*arr == NULL) {
			done = insert(*arr, attack);
		} else {
			if ((*arr)->compareType(*attack)) {
				done = insert(*arr, attack);
			} else {
				done = insert(++arr, attack);
			}
		}
	}
	return done;
}

//display helper function
void AddOnsDb::display() {
	display(table);
}

//recursively display all from pointer
void AddOnsDb::display(Attacks* ptr) {
	if (ptr) {
		cout << *ptr << endl;
		display(ptr->nextLink());
	}
}

//recursively display all from table
void AddOnsDb::display(Attacks** arr, int count) {
	if (arr != table + size) {
		cout << "List: " << count << endl;
		display(*arr);
		cout << endl;
		display(++arr, ++count);
	}
}

//increase size of table when more items of different types are added than original table size allowed
int AddOnsDb::incrSize() {
	int newSize = size + 5;
	Attacks** newTable = new Attacks*[newSize];
	init(newTable, newTable, newSize);
	copy(newTable, newTable, table);
	destroy(table);
	delete [] table;
	table = newTable;
	return newSize;
}

//retrieve an item and return a pointer
//idea is so user retrieving will make copy to add to their table
Attacks* AddOnsDb::retrieve() {
	return retrieve(table, "");
	
}

//retrieve an attack and return a pointer
//random number generator decides what type of attack is chosen
Attacks* AddOnsDb::retrieve(const mstr & type1, const mstr type2) {
	srand(time(NULL));
	int draw = rand() % 3 + 1;
	Attacks* temp = NULL;
	if (draw > 1) {
		temp =  retrieve(table, type1);
	} else {
		temp =  retrieve(table, type2);
	}
	return temp;
}

//retrieve an attack and return pointer recursion
//rand num gen decides what attack
Attacks* AddOnsDb::retrieve(Attacks* ptr, int & selection, bool & selected, int count) {
	Attacks* draw = NULL;
	if (ptr) {
		draw = retrieve(ptr->nextLink(), selection, selected, ++count);
		if (!selected) {
			srand(time(NULL));
			selection = rand() % count + 1;
			selected = true;
		}
		if (count == selection) {
			draw = ptr;
		}
	}
	return draw;
}

//retrieve an attack and return pointer array recursion
Attacks* AddOnsDb::retrieve(Attacks** arr, const mstr & type) {
	int selection = 0;
	bool selected = false;
	Attacks* draw = NULL;
	if (arr != table + size) {
		if (*arr && (*arr)->compareType(type)) {
			draw = retrieve(*arr, selection, selected);
		} else {
			draw = retrieve(++arr, type);
		}
	}
	return draw;
}

//add attacks from text file to populate the database
bool AddOnsDb::addAttacks(const char* file) {
	bool done = true;
	mstr string1, string2;
	int a, b, c;
	char buffer[100];

	ifstream myfile(file);
	if (myfile.is_open()) {
		while (myfile.peek() != EOF) {
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
			//insert(attack);
		} 
	} else {
		cout << "file can't open\n";
		done = false;
	}
	myfile.close();
	return done;
}

//add items from text file to populate database
bool AddOnsDb::addItems(const char* file) {
	bool done = true;
	mstr string1;
	int a;
	char buffer[100];

	ifstream myfile(file);
	if (myfile.is_open()) {
		while(myfile.peek() != EOF) {
			myfile.get(buffer, 100, ',');
			myfile.get();
			string1 = buffer;

			myfile.get(buffer, 100, ',');
			myfile.get();
			a = atoi(buffer);

			myfile.ignore(100, '\n');

			Items item(string1, a);
			*this += item;
			//insert(item);
		}
	} else {
		cout << "file can't open\n";
		done = false;
	}
	myfile.close();
	return done;
}

//+= operator overload
AddOnsDb & AddOnsDb::operator+= (const Attacks & attack) {
	insert(attack);
	return *this;
}

//+= operator overload
AddOnsDb & AddOnsDb::operator+= (const Items & item) {
	insert(item);
	return *this;
}



