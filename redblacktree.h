/*
Programmer: Mina Vu
Program:	Pokemon Battle Simulation
File name:  redblacktree.h
*/

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "pokemonsub.h"

// Data structure to hold captured Pokemons using binary search red-black tree
class RedBlackTree
{
private:
	enum
	{
		BLACK,
		RED
	};
	RedBlackTreeNode *root;

	void copy(RedBlackTreeNode *&, RedBlackTreeNode *);						 // recursively copy from one tree to another
	int height(RedBlackTreeNode *);											 // recursively find height of the tree
	void displayInorder(RedBlackTreeNode *, int &);							 // recursively display by inorder
	int insert(RedBlackTreeNode *&, RedBlackTreeNode *);					 // recursively insert a new pokemon
	RedBlackTreeNode *rightRotate(RedBlackTreeNode *&, RedBlackTreeNode *&); // rotate right for tree rebalance
	RedBlackTreeNode *leftRotate(RedBlackTreeNode *&, RedBlackTreeNode *&);	 // rotate left for tree rebalance
	void destroy(RedBlackTreeNode *&);										 // recursively destroy tree
	RedBlackTreeNode *retrieve(RedBlackTreeNode *, const string &);			 // recursively retrieve a pokemon from the tree by name
	void choose(RedBlackTreeNode *, RedBlackTreeNode *&, int, int &);		 // recursively select a pokemon from the tree by number
	int showGrown(RedBlackTreeNode *);										 // recursively find all pokemons that have leveled up
	void restore(RedBlackTreeNode *);										 // recursively restore all pokemons

public:
	RedBlackTree();
	RedBlackTree(const RedBlackTree &);
	~RedBlackTree();

	bool isEmpty() const;
	int height();
	int displayInorder();
	int insert(RedBlackTreeNode *);
	RedBlackTreeNode *retrieve(const string &);
	RedBlackTreeNode *choose(const char *);
	int showGrown();
	void restore();

	RedBlackTree &operator=(const RedBlackTree &);
};

#endif
