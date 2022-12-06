/*
Programmer: Mina Vu
Assignment: Prog3
File name:  redblack.h
Class:      CS202
Term:	    Fall 2020

This is the header file for class RedBlack.
RedBlack class is the data structure for the assignment.
*/

#ifndef REDBLACK_H
#define REDBLACK_H

#include "pokemon.h"

class RedBlack
{
private:
	enum
	{
		BLACK,
		RED
	};
	Pokemon *root;

	void copy(Pokemon *&, Pokemon *);				// copy from one tree to another
	int height(Pokemon *);							// find height of the tree
	void displayBreadth(Pokemon *, int);			// display by breadth of the tree
	void displayInorder(Pokemon *, int &);			// display by inorder
	void displayPreorder(Pokemon *);				// display by preorder
	int insert(Pokemon *&, Pokemon *);				// recursively insert a new pokemon
	Pokemon *rightRotate(Pokemon *&, Pokemon *&);	// rotate right for rebalance
	Pokemon *leftRotate(Pokemon *&, Pokemon *&);	// rotate left for rebalace
	void destroy(Pokemon *&);						// destroy tree
	Pokemon *retrieve(Pokemon *, const string &);	// retrieve a pokemon from the tree by name
	void choose(Pokemon *, Pokemon *&, int, int &); // select a pokemon form the tree by number
	int showGrown(Pokemon *);						// find all pokemons that have leveled up
	void restore(Pokemon *);						// restore all pokemons

public:
	RedBlack();					// default constructor
	RedBlack(const RedBlack &); // copy constructor
	~RedBlack();				// destructor

	bool isEmpty() const;					  // indicate if tree is empty or not
	int height();							  // find height helper function
	void displayBreadth();					  // display by breadth helper function
	int displayInorder();					  // display by inorder helper function
	void displayPreorder();					  // display by preorder helper functon
	int insert(string, AddOnsDb *, string = ""); // insert into tree by type indication only
	int insert(Pokemon *);					  // insert into tree with created pokemon
	Pokemon *retrieve(const string &);		  // retrieve pokemon by name
	Pokemon *choose(const char *);			  // select a pokemon with prompt
	int showGrown();						  // show grown helper function
	void restore();							  // restore helper function

	RedBlack &operator=(const RedBlack &); //= operator overload
};

#endif
