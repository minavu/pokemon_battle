/*
Programmer: Mina Vu
Assignment: Prog3
File name:  pokemon.cpp
Class:      CS202
Term:	    Fall 2020

This file contains the implementations for classes Pokemon, Pikachu, Charmander,
Squirtle, and Bulbasaur.  Pokemon is an ABC class.
Function information below.
*/

#include "pokemon.h"

// default constructor
Pokemon::Pokemon() : type(normal), status(alive), grown(0), level(0), exp(0), hp(0), maxHP(0), database(0), moves(0), lcolor(BLACK), rcolor(BLACK), left(0), right(0)
{
	moves = new AddOns *[MAX_MOVES];
	for (int i{0}; i < MAX_MOVES; ++i)
		moves[i] = nullptr;
}

// arg constructor takes a name and database pointer
Pokemon::Pokemon(AddOnsDb *db, string aName) : type(normal), status(alive), grown(0), level(0), exp(0), hp(0), maxHP(0), name(aName), database(db), moves(0), lcolor(BLACK), rcolor(BLACK), left(0), right(0)
{
	moves = new AddOns *[MAX_MOVES];
	for (int i{0}; i < MAX_MOVES; ++i)
		moves[i] = nullptr;
}

// copy constructor
Pokemon::Pokemon(const Pokemon &source) : type(source.type), status(source.status), grown(source.grown), level(source.level), exp(source.exp), hp(source.hp), maxHP(source.maxHP), name(source.name), database(0), moves(0), lcolor(BLACK), rcolor(BLACK), left(0), right(0)
{
	database = source.database;
	moves = new AddOns *[MAX_MOVES];
	for (int i{0}; i < MAX_MOVES; ++i)
		moves[i] = nullptr;
	copy(source.moves);
}

// destructor only sets database pointer to null and not delete
Pokemon::~Pokemon()
{
	database = NULL;
	destroy();
	delete[] moves;
	moves = NULL;
}

// copy all from source table
void Pokemon::copy(AddOns **source)
{
	if (source[ITEM])
		moves[ITEM] = new Items(*(dynamic_cast<Items *>(source[ITEM])));

	for (int i{1}; i < MAX_MOVES; ++i)
	{
		if (source[i])
		{
			moves[i] = new Attacks(*(dynamic_cast<Attacks *>(source[i])));
		}
	}
}

// destroy table
void Pokemon::destroy()
{
	for (int i{0}; i < MAX_MOVES; ++i)
		delete moves[i];
}

// display moves set helper function
int Pokemon::displayMoves() const
{
	int has{0};
	for (int i{1}; i < MAX_MOVES; ++i)
		if (moves[i])
		{
			++has;
			cout << has << ". " << *moves[i] << endl;
		}
	return has;
}

// display pokemon full information
void Pokemon::fullInfo() const
{
	char types[][10] = {"electric", "fire", "water", "grass", "normal"};
	char state[][10] = {"alive", "knock-out"};
	cout << "Type: " << types[type] << " pokemon" << endl;
	cout << "Level: " << level << endl;
	cout << "Status: " << state[status] << endl;
	cout << "Hp: " << hp << endl;
	if (holding())
	{
		cout << name << " is holding a " << *moves[ITEM] << endl;
	}
	else
	{
		cout << name << " is not holding any item\n";
	}
	cout << name << "'s moves set\n";
	displayMoves();
}

// display only pokemon battle stats
void Pokemon::battleStats() const
{
	char state[][10] = {"alive", "knock-out"};
	cout << name << "'s current stats-->level: " << level << ", status: " << state[status] << ", hp: " << hp;
	cout << endl;
}

// learn helper function
bool Pokemon::learn()
{
	char translate[][10] = {"electric", "fire", "water", "grass", "normal"};
	string mtype = translate[type];

	if (!database)
	{
		cout << "Must add address of AddOnsDb database to initialize pokemon.\n";
		return false;
	}

	AddOns *temp = new Attacks(*(dynamic_cast<Attacks *>(database->retrieve(mtype))));
	cout << name << " wants to learn a new attack! --> " << *temp << endl;
	char answer = minalib::getYesNo("Do you want to teach your pokemon the above attack (y/n)? ");
	if (toupper(answer) == 'N')
	{
		cout << name << " did not learn " << *temp << endl;
		delete temp;
		return false;
	}

	bool added{false};
	for (int i{1}; i < MAX_MOVES; ++i)
	{
		if (!moves[i])
		{
			moves[i] = temp;
			added = true;
			break;
		}
	}
	if (!added)
	{
		cout << name << " is full of moves\n";
		added = switchAttacks(temp);
		if (!added)
		{
			cout << name << " did not learn " << *temp << endl;
			delete temp;
		}
	}
	if (added)
		grown = false;
	return added;
}

// prompt user to select a move from moves set to switch out for new move
// return false if user decides not to switch
bool Pokemon::switchAttacks(AddOns *attack)
{
	bool done = false;
	cout << "0) go back\n";
	displayMoves();
	int select = minalib::getInt("Select a move to replace: ", 0, MOVES);
	cout << "You selected " << select << endl;
	if (select > 0)
	{
		delete moves[select];
		moves[select] = attack;
		done = true;
	}
	return done;
}

// initializes pokemon with level, hp, and starting move
bool Pokemon::initialize()
{
	bool done = false;
	if (database)
	{
		moves[1] = new Attacks(*(dynamic_cast<Attacks *>(database->retrieve("normal"))));
		++level;
		hp += 500;
		maxHP += 500;
		done = true;
	}
	else
	{
		cout << "Must add database\n";
	}
	return done;
}

// add new item to moves set else indicate pokemon is holding an item already
bool Pokemon::hold(const Items &item)
{
	bool take = false;
	if (!holding())
	{
		moves[ITEM] = new Items(item);
		take = true;
	}
	else
	{
		cout << name << " is holding " << item << endl;
	}
	return take;
}

//+= operator overload
Pokemon &Pokemon::operator+=(const Items &item)
{
	hold(item);
	return *this;
}

// indicate pokemon is holding an item or not
bool Pokemon::holding() const
{
	return moves[ITEM] != NULL;
}

// attack an opponent pokemon by having user select attack from move set
// if attack has no pp left, require user to select a different move
// level up pokemon a little bit and calls opponent hit function
bool Pokemon::attack(Pokemon &opponent)
{
	int count = displayMoves();
	int select = minalib::getInt("Select a move from above to attack: ", 1, count);
	bool usable = moves[select]->use();
	while (!usable)
	{
		select = minalib::getInt("No more PP left. Select another move to attack: ", 1, count);
		usable = moves[select]->use();
	}
	cout << "You attack with " << *moves[select] << endl;
	if (levelUp())
	{
		cout << name << " gained enough experiece to increase to level " << level << "!\n";
	}
	return opponent.hit(*(dynamic_cast<Attacks *>(moves[select])));
}

// return pokemon state for battle use
bool Pokemon::state()
{
	return status == alive ? true : false;
}

// restore pokemon to healthy level
void Pokemon::restore()
{
	status = alive;
	hp = maxHP;
	for (int i{1}; i < MAX_MOVES; ++i)
		if (moves[i])
		{
			Attacks *attack = dynamic_cast<Attacks *>(moves[i]);
			attack->restore();
		}
}

// increase a pokemon's level by increasing its experience
bool Pokemon::levelUp()
{
	bool increased = false;
	exp += 200;
	if (exp / (level * 500) == 1)
	{
		exp -= (level * 500);
		++level;
		maxHP += 500;
		grown = true;
		increased = true;
	}
	return increased;
}

// indicate pokemon as leveled up
bool Pokemon::hasGrown()
{
	return grown;
}

// allow for change name
void Pokemon::changeName(const string &newName)
{
	name = newName;
}

//= operator overloading
Pokemon &Pokemon::operator=(Pokemon &source)
{
	if (&source != this)
	{
		type = source.type;
		status = source.status;
		level = source.level;
		exp = source.exp;
		hp = source.hp;
		maxHP = source.maxHP;
		name = source.name;
		database = source.database;

		destroy();
		delete[] moves;
		moves = new AddOns *[MAX_MOVES];
		copy(source.moves);
	}
	return *this;
}

//<< operator overloading
ostream &operator<<(ostream &os, const Pokemon &pokemon)
{
	pokemon.display(os);
	return os;
}

//>> operator overload
istream &operator>>(istream &is, Pokemon &pokemon)
{
	is >> pokemon.name;
	return is;
}

string operator+(const string &str, const Pokemon &pokemon)
{
	return str + pokemon.name;
}

string operator+(const Pokemon &pokemon, const string &str)
{
	return pokemon.name + str;
}

string operator+(const Pokemon &pokemon1, const Pokemon &pokemon2)
{
	return pokemon1.name + pokemon2.name;
}

//== operator overload
bool operator==(const Pokemon &str1, const Pokemon &str2)
{
	return str1.name == str2.name;
}

//== operator overload
bool operator==(const Pokemon &str1, const string &str2)
{
	return str1.name == str2;
}

//== operator overload
bool operator==(const string &str1, const Pokemon &str2)
{
	return str1 == str2.name;
}

//!= operator overload
bool operator!=(const Pokemon &str1, const Pokemon &str2)
{
	return str1.name != str2.name;
}

//!= operator overload
bool operator!=(const Pokemon &str1, const string &str2)
{
	return str1.name != str2;
}

//!= operator overload
bool operator!=(const string &str1, const Pokemon &str2)
{
	return str1 != str2.name;
}

//<= operator overload
bool operator<=(const Pokemon &str1, const Pokemon &str2)
{
	return str1.name <= str2.name;
}

//<= operator overload
bool operator<=(const Pokemon &str1, const string &str2)
{
	return str1.name <= str2;
}

//<= operator overload
bool operator<=(const string &str1, const Pokemon &str2)
{
	return str1 <= str2.name;
}

//>= operator overload
bool operator>=(const Pokemon &str1, const Pokemon &str2)
{
	return str1.name >= str2.name;
}

//>= operator overload
bool operator>=(const Pokemon &str1, const string &str2)
{
	return str1.name >= str2;
}

//>= operator overload
bool operator>=(const string &str1, const Pokemon &str2)
{
	return str1 >= str2.name;
}

//< operator overload
bool operator<(const Pokemon &str1, const Pokemon &str2)
{
	return str1.name < str2.name;
}

//< operator overload
bool operator<(const Pokemon &str1, const string &str2)
{
	return str1.name < str2;
}

//< operator overload
bool operator<(const string &str1, const Pokemon &str2)
{
	return str1 < str2.name;
}

//> operator overload
bool operator>(const Pokemon &str1, const Pokemon &str2)
{
	return str1.name > str2.name;
}

//> operator overload
bool operator>(const Pokemon &str1, const string &str2)
{
	return str1.name > str2;
}

//> operator overload
bool operator>(const string &str1, const Pokemon &str2)
{
	return str1 > str2.name;
}

// connect with left child in RB tree
Pokemon *&Pokemon::leftLink()
{
	return left;
}

// connect with right child in RB tree
Pokemon *&Pokemon::rightLink()
{
	return right;
}

// return color of left child
bool &Pokemon::leftColor()
{
	return lcolor;
}

// return color of right child
bool &Pokemon::rightColor()
{
	return rcolor;
}

// default constructor
Pikachu::Pikachu() : factor(0)
{
	factor = new float[TYPES]{1.0, 2.0, 2.0, 1.0, 1.0};
	type = electric;
}

// arg constructor
Pikachu::Pikachu(AddOnsDb *db, string aName) : Pokemon(db, aName), factor(0)
{
	factor = new float[TYPES]{1.0, 2.0, 2.0, 1.0, 1.0};
	type = electric;
}

// copy constructor
Pikachu::Pikachu(const Pikachu &source) : Pokemon(source), factor(0)
{
	factor = new float[source.TYPES];
	for (int i = 0; i < source.TYPES; ++i)
	{
		factor[i] = source.factor[i];
	}
	type = source.type;
}

// destructor
Pikachu::~Pikachu()
{
	delete[] factor;
	factor = NULL;
}

// display pikachu name
// had more to this before ideas changed
void Pikachu::display(ostream &os) const
{
	os << name;
}

// display pikachu's full information
void Pikachu::fullInfo() const
{
	cout << "Your Pikachu's name is: " << name << endl;
	Pokemon::fullInfo();
}

// takes damage an attack, use item if holding item, and change status if hp reaches 0
bool Pikachu::hit(const Attacks &attack)
{
	bool hurt = false;
	int damage = attack.calcDamage(factor, type);
	if (damage)
	{
		hp -= damage;
		hurt = true;
	}
	else
	{
		cout << "Hooray! " << name << " dodged the attack!\n";
	}
	if (hp < 100 && hp > 0 && holding())
	{
		hp += moves[ITEM]->use();
		cout << name << " used " << *moves[ITEM] << " to increase its hp by a little!\n";
		delete moves[ITEM];
		moves[ITEM] = NULL;
	}
	if (hp <= 0)
	{
		hp = 0;
		status = ko;
	}
	return hurt;
}

//= operator overload
Pikachu &Pikachu::operator=(Pikachu &source)
{
	if (&source != this)
	{
		Pokemon::operator=(source);
		delete[] factor;
		factor = new float[source.TYPES];
		for (int i = 0; i < source.TYPES; ++i)
		{
			factor[i] = source.factor[i];
		}
		type = source.type;
	}
	return *this;
}

// default constructor
Charmander::Charmander() : factor(0)
{
	factor = new float[TYPES]{2.0, 1.0, 0.5, 2.5, 1.0};
	type = fire;
}

// arg constructor
Charmander::Charmander(AddOnsDb *db, string aName) : Pokemon(db, aName), factor(0)
{
	factor = new float[TYPES]{2.0, 1.0, 0.5, 2.5, 1.0};
	type = fire;
}

// copy constructor
Charmander::Charmander(const Charmander &source) : Pokemon(source), factor(0)
{
	factor = new float[source.TYPES];
	for (int i = 0; i < source.TYPES; ++i)
	{
		factor[i] = source.factor[i];
	}
	type = source.type;
}

// destructor
Charmander::~Charmander()
{
	delete[] factor;
	factor = NULL;
}

// display charmander's name
void Charmander::display(ostream &os) const
{
	os << name;
}

// display charmander's full info
void Charmander::fullInfo() const
{
	cout << "Your Charmander's name is: " << name << endl;
	Pokemon::fullInfo();
}

// take damage from an attack, use item if holding, change status if knocked out
bool Charmander::hit(const Attacks &attack)
{
	bool hurt = false;
	int damage = attack.calcDamage(factor, type);
	if (damage)
	{
		hp -= damage;
		hurt = true;
	}
	else
	{
		cout << "Hooray! " << name << " dodged the attack!\n";
	}
	if (hp < 100 && hp > 0 && holding())
	{
		hp += moves[ITEM]->use();
		cout << name << " used " << *moves[ITEM] << " to increase its hp by a little!\n";
		delete moves[ITEM];
		moves[ITEM] = NULL;
	}
	if (hp <= 0)
	{
		hp = 0;
		status = ko;
	}
	return hurt;
}

//= operator overload
Charmander &Charmander::operator=(Charmander &source)
{
	if (&source != this)
	{
		Pokemon::operator=(source);
		delete[] factor;
		factor = new float[source.TYPES];
		for (int i = 0; i < source.TYPES; ++i)
		{
			factor[i] = source.factor[i];
		}
		type = source.type;
	}
	return *this;
}

// default constructor
Squirtle::Squirtle() : factor(0)
{
	factor = new float[TYPES]{2.0, 2.5, 1.0, 0.5, 1.0};
	type = water;
}

// arg constructor
Squirtle::Squirtle(AddOnsDb *db, string aName) : Pokemon(db, aName), factor(0)
{
	factor = new float[TYPES]{2.0, 2.5, 1.0, 0.5, 1.0};
	type = water;
}

// copy constructor
Squirtle::Squirtle(const Squirtle &source) : Pokemon(source), factor(0)
{
	factor = new float[source.TYPES];
	for (int i = 0; i < source.TYPES; ++i)
	{
		factor[i] = source.factor[i];
	}
	type = source.type;
}

// destructor
Squirtle::~Squirtle()
{
	delete[] factor;
	factor = NULL;
}

// display squirtle's name
void Squirtle::display(ostream &os) const
{
	os << name;
}

// display full info
void Squirtle::fullInfo() const
{
	cout << "Your Squirtle's name is: " << name << endl;
	Pokemon::fullInfo();
}

// take damage from an attack
bool Squirtle::hit(const Attacks &attack)
{
	bool hurt = false;
	int damage = attack.calcDamage(factor, type);
	if (damage)
	{
		hp -= damage;
		hurt = true;
	}
	else
	{
		cout << "Hooray! " << name << " dodged the attack!\n";
	}
	if (hp < 100 && hp > 0 && holding())
	{
		hp += moves[ITEM]->use();
		cout << name << " used " << *moves[ITEM] << " to increase its hp by a little!\n";
		delete moves[ITEM];
		moves[ITEM] = NULL;
	}
	if (hp <= 0)
	{
		hp = 0;
		status = ko;
	}
	return hurt;
}

//= operator overload
Squirtle &Squirtle::operator=(Squirtle &source)
{
	if (&source != this)
	{
		Pokemon::operator=(source);
		delete[] factor;
		factor = new float[source.TYPES];
		for (int i = 0; i < source.TYPES; ++i)
		{
			factor[i] = source.factor[i];
		}
		type = source.type;
	}
	return *this;
}

// default constructor
Bulbasaur::Bulbasaur() : factor(0)
{
	factor = new float[TYPES]{1.0, 0.5, 2.5, 1.0, 1.0};
	type = grass;
}

// arg constructor
Bulbasaur::Bulbasaur(AddOnsDb *db, string aName) : Pokemon(db, aName), factor(0)
{
	factor = new float[TYPES]{1.0, 0.5, 2.5, 1.0, 1.0};
	type = grass;
}

// copy construcotr
Bulbasaur::Bulbasaur(const Bulbasaur &source) : Pokemon(source), factor(0)
{
	factor = new float[source.TYPES];
	for (int i = 0; i < source.TYPES; ++i)
	{
		factor[i] = source.factor[i];
	}
	type = source.type;
}

// destructor
Bulbasaur::~Bulbasaur()
{
	delete[] factor;
	factor = NULL;
}

// display Bulbasaur's name
void Bulbasaur::display(ostream &os) const
{
	os << name;
}

// display full information
void Bulbasaur::fullInfo() const
{
	cout << "Your Bulbasaur's name is: " << name << endl;
	Pokemon::fullInfo();
}

// take damage from an attack
// these were placed in the derived class because of an early idea that didn't pan out
bool Bulbasaur::hit(const Attacks &attack)
{
	bool hurt = false;
	int damage = attack.calcDamage(factor, type);
	if (damage)
	{
		hp -= damage;
		hurt = true;
	}
	else
	{
		cout << "Hooray! " << name << " dodged the attack!\n";
	}
	if (hp < 100 && hp > 0 && holding())
	{
		hp += moves[ITEM]->use();
		cout << name << " used " << *moves[ITEM] << " to increase its hp by a little!\n";
		delete moves[ITEM];
		moves[ITEM] = NULL;
	}
	if (hp <= 0)
	{
		hp = 0;
		status = ko;
	}
	return hurt;
}

//= operator overload
Bulbasaur &Bulbasaur::operator=(Bulbasaur &source)
{
	if (&source != this)
	{
		Pokemon::operator=(source);
		delete[] factor;
		factor = new float[source.TYPES];
		for (int i = 0; i < source.TYPES; ++i)
		{
			factor[i] = source.factor[i];
		}
		type = source.type;
	}
	return *this;
}
