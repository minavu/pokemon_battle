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
	void copy(AddOns** source);			 // copy array recursion for moves array
	void destroy();					 // destroy array recursion for moves array
	bool switchAttacks(AddOns* attack);	 // switch out a current move for a new move

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
	AddOnsDb* database;
	AddOns** moves;

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
	Pokemon(AddOnsDb *, string); // arg constructor takes pointer to database
	Pokemon(const Pokemon &);	 // copy constructor
	virtual ~Pokemon();			 // destructor

	bool initialize();					   // create the baby pokemon
	int displayMoves() const;			   // display move set
	bool learn();						   // helper function because each pokemon knows their type
	bool hold(const Items &);			   // have pokemon hold item
	bool holding() const;				   // return true if moves[ITEM] contains item
	bool attack(Pokemon &);				   // attack the pokemon
	int translate(const Attacks &) const;  // translate into types int
	void restore();						   // restore hp and attacks pp
	virtual bool hit(const Attacks &) = 0; // take a hit from the opponent
	bool levelUp();						   // increase experience then in turn level/maxHP
	bool hasGrown();					   // indicate growth since last learn
	void changeName(const string &);	   // set new name
	bool state();						   // return status for battle

	virtual void display(ostream &) const = 0; // display Pokemon
	virtual void fullInfo() const;			   // display all info
	void battleStats() const;				   // display only name, level, hp

	Pokemon *&leftLink();  // return left pointer
	Pokemon *&rightLink(); // return right pointer
	bool &leftColor();	   // return left color for redblack tree
	bool &rightColor();	   // return right color for redblack tree

	int whatOp(const char *) const;					   // determine what operator for comparison
	bool compare(const Pokemon &, const char *) const; // compare member function
	Pokemon &operator=(Pokemon &);					   //= operator overload
	Pokemon &operator+=(const Items &);				   //+= operator overload to hold item

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
private:
	float *factor;

public:
	Pikachu();										  // default constructor
	explicit Pikachu(AddOnsDb *, string = "Pikachu"); // arg constructor
	Pikachu(const Pikachu &);						  // copy constructor
	~Pikachu();										  // destructor

	bool hit(const Attacks &);	   // take a hit from the opponent
	void display(ostream &) const; // display Pikachu
	void fullInfo() const;		   // display all info

	Pikachu &operator=(Pikachu &); // overload = operator
};

class Charmander : public Pokemon
{
private:
	float *factor;

public:
	Charmander();											// default constructor
	explicit Charmander(AddOnsDb *, string = "Charmander"); // arg constructor
	Charmander(const Charmander &);							// copy constructor
	~Charmander();											// destructor

	bool hit(const Attacks &);	   // take a hit from the opponent
	void display(ostream &) const; // display Charmander
	void fullInfo() const;		   // display all info

	Charmander &operator=(Charmander &); // overload = operator
};

class Squirtle : public Pokemon
{
private:
	float *factor;

public:
	Squirtle();											// default constructor
	explicit Squirtle(AddOnsDb *, string = "Squirtle"); // arg constructor
	Squirtle(const Squirtle &);							// copy constructor
	~Squirtle();										// destructor

	bool hit(const Attacks &);	   // take a hit from the opponent
	void display(ostream &) const; // display Squirtle
	void fullInfo() const;		   // display all info

	Squirtle &operator=(Squirtle &); // overload = operator
};

class Bulbasaur : public Pokemon
{
private:
	float *factor;

public:
	Bulbasaur();										  // default constructor
	explicit Bulbasaur(AddOnsDb *, string = "Bulbasaur"); // arg constructor
	Bulbasaur(const Bulbasaur &);						  // copy constructor
	~Bulbasaur();										  // destructor

	bool hit(const Attacks &);	   // take a hit from the opponent
	void display(ostream &) const; // display Bulbasaur
	void fullInfo() const;		   // display all info

	Bulbasaur &operator=(Bulbasaur &); // overload = operator
};

#endif
