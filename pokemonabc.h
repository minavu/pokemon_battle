/*
Programmer: Mina Vu
Program:	Pokemon Battle Simulation
File name:  pokemonabc.h
*/

#ifndef POKEMONABC_H
#define POKEMONABC_H

#include <iostream>
#include "redblacktreenode.h"

using namespace std;

// Pokemon is an abstract base class
class Pokemon : public RedBlackTreeNode
{
private:
	void copyMovesList(AddOns **source); // copy array recursion for moves array
	void destroyMovesList();			 // destroy array recursion for moves array
	bool switchAttacks(AddOns *attack);	 // switch out a current move for a new move

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

public:
	Pokemon();
	Pokemon(const Pokemon &);
	virtual ~Pokemon() = 0;

	virtual void displayFullInfo() const;
	bool initialize(AddOnsDb *db);
	int displayAttacks() const;
	bool learnNewAttack();
	bool holdItem(const Items &);
	bool isHoldingItem() const;
	bool attack(Pokemon &);
	bool takeHit(const Attacks &);
	void restore();
	bool levelUp();
	bool hasGrown(); // indicate growth since last learn
	void changeName(const string &);
	bool isAlive();

	void displayBattleStats() const;

	Pokemon &operator=(Pokemon &);
	Pokemon &operator+=(const Items &);

	friend string operator+(const string &, const Pokemon &);
	friend string operator+(const Pokemon &, const string &);

	friend bool operator==(const Pokemon &, const Pokemon &);
	friend bool operator==(const Pokemon &, const string &);
	friend bool operator==(const string &, const Pokemon &);
	friend bool operator!=(const Pokemon &, const Pokemon &);
	friend bool operator!=(const Pokemon &, const string &);
	friend bool operator!=(const string &, const Pokemon &);
	friend bool operator<=(const Pokemon &, const Pokemon &);
	friend bool operator<=(const Pokemon &, const string &);
	friend bool operator<=(const string &, const Pokemon &);
	friend bool operator<(const Pokemon &, const Pokemon &);
	friend bool operator<(const Pokemon &, const string &);
	friend bool operator<(const string &, const Pokemon &);
	friend bool operator>=(const Pokemon &, const Pokemon &);
	friend bool operator>=(const Pokemon &, const string &);
	friend bool operator>=(const string &, const Pokemon &);
	friend bool operator>(const Pokemon &, const Pokemon &);
	friend bool operator>(const Pokemon &, const string &);
	friend bool operator>(const string &, const Pokemon &);

	friend ostream &operator<<(ostream &, const Pokemon &);
	friend istream &operator>>(istream &, Pokemon &);
};

#endif
