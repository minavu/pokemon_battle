/*
Programmer: Mina Vu
Assignment: Prog3
File name:  pokemon.h
Class:      CS202
Term:	    Fall 2020

This is the header file for abstract base class Pokemon and its derived classes
Pikachu, Charmander, Squirtle, and Bulbasaur.  Each Pokemon derived classes takes
a pointer to the attacks/items database to populate their moves set.
*/

#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include "addonsdb.h"

using namespace std;

class Pokemon
{
private:
	void copy(AddOns **source);			// copy array recursion for moves array
	void destroyMovesList();			// destroy array recursion for moves array
	bool switchAttacks(AddOns *attack); // switch out a current move for a new move

protected:
	enum
	{
		ITEM = 0,
		MOVES = 4,
		MAX_MOVES = 5,
		TYPES = 5
	};
	enum
	{
		electric,
		fire,
		water,
		grass,
		normal
	} type;
	enum
	{
		alive,
		ko
	} status;
	bool grown;
	int level;
	int exp;
	int hp;
	int maxHP;
	string name;
	AddOnsDb *database;
	float *factor;
	AddOns **moves;

	enum
	{
		BLACK,
		RED
	};
	bool lcolor;
	bool rcolor;
	Pokemon *left;
	Pokemon *right;

public:
	Pokemon();					 // default constructor
	Pokemon(const Pokemon &);	 // copy constructor
	virtual ~Pokemon() = 0;			 // destructor

	virtual void displayFullInfo() const;	   // display all info
	bool hit(const Attacks &);	   // take a hit from the opponent
	bool initialize(AddOnsDb* db);				 // create the baby pokemon
	int displayMoves() const;		 // display move set
	bool learnNewAttack();			 // helper function because each pokemon knows their type
	bool hold(const Items &);		 // have pokemon hold item
	bool isHoldingItem() const;		 // return true if moves[ITEM] contains item
	bool attack(Pokemon &);			 // attack the pokemon
	void restore();					 // restore hp and attacks pp
	bool levelUp();					 // increase experience then in turn level/maxHP
	bool hasGrown();				 // indicate growth since last learn
	void changeName(const string &); // set new name
	bool isAlive();					 // return status for battle

	void displayBattleStats() const; // display only name, level, hp

	Pokemon *&leftLink();  // return left pointer
	Pokemon *&rightLink(); // return right pointer
	bool &leftColor();	   // return left color for redblack tree
	bool &rightColor();	   // return right color for redblack tree

	Pokemon &operator=(Pokemon &);		//= operator overload
	Pokemon &operator+=(const Items &); //+= operator overload to hold item

	friend string operator+(const string &, const Pokemon &);
	friend string operator+(const Pokemon &, const string &);
	friend string operator+(const Pokemon &, const Pokemon &);

	friend bool operator==(const Pokemon &, const Pokemon &); //== operator overload
	friend bool operator==(const Pokemon &, const string &);  //== operator overload
	friend bool operator==(const string &, const Pokemon &);  //== operator overload
	friend bool operator!=(const Pokemon &, const Pokemon &); //!= operator overload
	friend bool operator!=(const Pokemon &, const string &);  //!= operator overload
	friend bool operator!=(const string &, const Pokemon &);  //!= operator overload
	friend bool operator<=(const Pokemon &, const Pokemon &); //<= operator overload
	friend bool operator<=(const Pokemon &, const string &);  //<= operator overload
	friend bool operator<=(const string &, const Pokemon &);  //<= operator overload
	friend bool operator>=(const Pokemon &, const Pokemon &); //>= operator overload
	friend bool operator>=(const Pokemon &, const string &);  //>= operator overload
	friend bool operator>=(const string &, const Pokemon &);  //>= operator overload
	friend bool operator<(const Pokemon &, const Pokemon &);  //< operator overload
	friend bool operator<(const Pokemon &, const string &);	  //< operator overload
	friend bool operator<(const string &, const Pokemon &);	  //< operator overload
	friend bool operator>(const Pokemon &, const Pokemon &);  //> operator overload
	friend bool operator>(const Pokemon &, const string &);	  //> operator overload
	friend bool operator>(const string &, const Pokemon &);	  //> operator overload

	friend ostream &operator<<(ostream &, const Pokemon &); // overload << operator
	friend istream &operator>>(istream &, Pokemon &);		// overload << operator
};

class Pikachu : public Pokemon
{
public:
	Pikachu();										  // default constructor
	Pikachu(const Pikachu &);						  // copy constructor
	Pikachu &operator=(Pikachu &); // overload = operator

	void displayFullInfo() const;  // display all info
};

class Charmander : public Pokemon
{
public:
	Charmander();											// default constructor
	Charmander(const Charmander &);							// copy constructor
	Charmander &operator=(Charmander &); // overload = operator

	void displayFullInfo() const;  // display all info
};

class Squirtle : public Pokemon
{
public:
	Squirtle();											// default constructor
	Squirtle(const Squirtle &);							// copy constructor
	Squirtle &operator=(Squirtle &); // overload = operator

	void displayFullInfo() const;  // display all info
};

class Bulbasaur : public Pokemon
{
public:
	Bulbasaur();										  // default constructor
	Bulbasaur(const Bulbasaur &);						  // copy constructor
	Bulbasaur &operator=(Bulbasaur &); // overload = operator

	void displayFullInfo() const;  // display all info
};

#endif
