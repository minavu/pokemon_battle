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
	RedBlackTreeNode *root;

	void copy(RedBlackTreeNode *&, RedBlackTreeNode *);				// copy from one tree to another
	int height(RedBlackTreeNode *);							// find height of the tree
	void displayInorder(RedBlackTreeNode *, int &);			// display by inorder
	int insert(RedBlackTreeNode *&, RedBlackTreeNode *);				// recursively insert a new pokemon
	RedBlackTreeNode *rightRotate(RedBlackTreeNode *&, RedBlackTreeNode *&);	// rotate right for rebalance
	RedBlackTreeNode *leftRotate(RedBlackTreeNode *&, RedBlackTreeNode *&);	// rotate left for rebalace
	void destroy(RedBlackTreeNode *&);						// destroy tree
	RedBlackTreeNode *retrieve(RedBlackTreeNode *, const string &);	// retrieve a pokemon from the tree by name
	void choose(RedBlackTreeNode *, RedBlackTreeNode *&, int, int &); // select a pokemon form the tree by number
	int showGrown(RedBlackTreeNode *);						// find all pokemons that have leveled up
	void restore(RedBlackTreeNode *);						// restore all pokemons

public:
	RedBlackTree();						// default constructor
	RedBlackTree(const RedBlackTree &); // copy constructor
	~RedBlackTree();					// destructor

	bool isEmpty() const;			   // indicate if tree is empty or not
	int height();					   // find height helper function
	int displayInorder();			   // display by inorder helper function
	int insert(RedBlackTreeNode *);			   // insert into tree with created pokemon
	RedBlackTreeNode *retrieve(const string &); // retrieve pokemon by name
	RedBlackTreeNode *choose(const char *);	   // select a pokemon with prompt
	int showGrown();				   // show grown helper function
	void restore();					   // restore helper function

	RedBlackTree &operator=(const RedBlackTree &); //= operator overload
};

#endif
