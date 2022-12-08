/*
Programmer: Mina Vu
Assignment: Prog3
File name:  redblacktree.h
Class:      CS202
Term:	    Fall 2020

This is the header file for class RedBlackTree.
RedBlackTree class is the data structure for the assignment.
*/

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "pokemonsub.h"

class RedBlackTree
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
	void displayInorder(Pokemon *, int &);			// display by inorder
	int insert(Pokemon *&, Pokemon *);				// recursively insert a new pokemon
	Pokemon *rightRotate(Pokemon *&, Pokemon *&);	// rotate right for rebalance
	Pokemon *leftRotate(Pokemon *&, Pokemon *&);	// rotate left for rebalace
	void destroy(Pokemon *&);						// destroy tree
	Pokemon *retrieve(Pokemon *, const string &);	// retrieve a pokemon from the tree by name
	void choose(Pokemon *, Pokemon *&, int, int &); // select a pokemon form the tree by number
	int showGrown(Pokemon *);						// find all pokemons that have leveled up
	void restore(Pokemon *);						// restore all pokemons

public:
	RedBlackTree();						// default constructor
	RedBlackTree(const RedBlackTree &); // copy constructor
	~RedBlackTree();					// destructor

	bool isEmpty() const;			   // indicate if tree is empty or not
	int height();					   // find height helper function
	int displayInorder();			   // display by inorder helper function
	int insert(Pokemon *);			   // insert into tree with created pokemon
	Pokemon *retrieve(const string &); // retrieve pokemon by name
	Pokemon *choose(const char *);	   // select a pokemon with prompt
	int showGrown();				   // show grown helper function
	void restore();					   // restore helper function

	RedBlackTree &operator=(const RedBlackTree &); //= operator overload
};

#endif
