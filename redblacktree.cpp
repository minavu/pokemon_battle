/*
Programmer: Mina Vu
Assignment: Prog3
File name:  redblacktree.cpp
Class:      CS202
Term:	    Fall 2020

This file contains all the implementations for class RedBlackTree.
Some functions were later not used because better ideas materialized.
Function information below.
*/

#include "redblacktree.h"

// default constructor
RedBlackTree::RedBlackTree() : root(0) {}

// copy constructor
RedBlackTree::RedBlackTree(const RedBlackTree &source) : root(0)
{
	if (source.root)
	{
		copy(root, source.root);
	}
}

// copy function copy from source root to destination root recursively
// assuming that destination root is null before processing
void RedBlackTree::copy(Pokemon *&dstPtr, Pokemon *srcPtr)
{
	if (srcPtr)
	{
		if (typeid(*srcPtr) == typeid(Pikachu))
		{
			dstPtr = new Pikachu(*(dynamic_cast<Pikachu *>(srcPtr)));
		}
		else if (typeid(*srcPtr) == typeid(Charmander))
		{
			dstPtr = new Charmander(*(dynamic_cast<Charmander *>(srcPtr)));
		}
		else if (typeid(*srcPtr) == typeid(Squirtle))
		{
			dstPtr = new Squirtle(*(dynamic_cast<Squirtle *>(srcPtr)));
		}
		else if (typeid(*srcPtr) == typeid(Bulbasaur))
		{
			dstPtr = new Bulbasaur(*(dynamic_cast<Bulbasaur *>(srcPtr)));
		}
		copy(dstPtr->leftLink(), srcPtr->leftLink());
		copy(dstPtr->rightLink(), srcPtr->rightLink());
	}
}

//= operator overload
RedBlackTree &RedBlackTree::operator=(const RedBlackTree &source)
{
	if (&source != this)
	{
		if (root)
		{
			destroy(root);
		}
		copy(root, source.root);
	}
	return *this;
}

// destructor
RedBlackTree::~RedBlackTree()
{
	destroy(root);
}

// indicate if tree is empty or not
bool RedBlackTree::isEmpty() const
{
	return (!root) ? true : false;
}

// height function helper
int RedBlackTree::height()
{
	return height(root);
}

// recursively find height of tree
int RedBlackTree::height(Pokemon *ptr)
{
	int level = 0;
	if (ptr)
	{
		int lheight = height(ptr->leftLink());
		int rheight = height(ptr->rightLink());
		if (lheight > rheight)
		{
			level = lheight + 1;
		}
		else
		{
			level = rheight + 1;
		}
	}
	return level;
}

// display tree by breadth
void RedBlackTree::displayBreadth()
{
	int h = height(root);
	for (int i = 1; i <= h; ++i)
	{
		cout << "Level " << i << ":  ";
		displayBreadth(root, i);
		cout << endl;
	}
}

// recursively display tree by breadth
void RedBlackTree::displayBreadth(Pokemon *ptr, int level)
{
	if (ptr)
	{
		if (level == 1)
		{
			cout << *ptr << ", colors are: " << ptr->leftColor() << "/" << ptr->rightColor() << "\t";
		}
		else
		{
			displayBreadth(ptr->leftLink(), level - 1);
			displayBreadth(ptr->rightLink(), level - 1);
		}
	}
}

// insert pokemon pointer
int RedBlackTree::insert(Pokemon *pokemon)
{
	return insert(root, pokemon);
}

// insert pokemon by type indication
int RedBlackTree::insert(string draw, AddOnsDb *database, string name)
{
	Pokemon *toAdd = NULL;
	if (draw == "Pikachu")
	{
		if (name != "")
		{
			toAdd = new Pikachu(database, name);
		}
		else
		{
			toAdd = new Pikachu(database);
		}
	}
	if (draw == "Charmander")
	{
		if (name != "")
		{
			toAdd = new Charmander(database, name);
		}
		else
		{
			toAdd = new Charmander(database);
		}
	}
	if (draw == "Squirtle")
	{
		if (name != "")
		{
			toAdd = new Squirtle(database, name);
		}
		else
		{
			toAdd = new Squirtle(database);
		}
	}
	if (draw == "Bulbasaur")
	{
		if (name != "")
		{
			toAdd = new Bulbasaur(database, name);
		}
		else
		{
			toAdd = new Bulbasaur(database);
		}
	}
	toAdd->initialize();
	return insert(root, toAdd);
}

// insert pokemon recursively and maintain properties of a redblack tree
// this is the bulk of the work!
int RedBlackTree::insert(Pokemon *&ptr, Pokemon *pokemon)
{
	int lineage = 0;
	if (!ptr)
	{
		ptr = pokemon;
	}
	else
	{
		if (*pokemon < *ptr)
		{
			lineage = 1 + insert(ptr->leftLink(), pokemon);
			if (lineage == 1)
			{ // found parent
				if (ptr->leftLink()->leftColor() != RED)
				{
					ptr->leftColor() = RED; // new child is always red, unless it has children
				}
			}
			if (lineage == 2)
			{ // found grandparent
				// if new child's parent and aunt are both red
				if (ptr->leftColor() == RED && ptr->rightColor() == RED)
				{
					ptr->leftColor() = ptr->rightColor() = BLACK;
					lineage = 0;
					// if new child's parent is red but aunt is black
				}
				else if (ptr->leftColor() == RED && ptr->leftLink()->leftColor() == RED)
				{ // this is when ptr is not grandparent to val but needs to rotate
					// left-left case, where child is left of parent and parent is left of granny
					ptr = rightRotate(ptr->leftLink(), ptr);
					lineage = 0;
				}
				else if (ptr->leftColor() == RED && ptr->leftLink()->rightColor() == RED)
				{ // this is when ptr is not grandparent to val but needs to rotate
					// left-right case, where child is right of parent and parent is left of granny
					Pokemon *parent = ptr->leftLink();
					Pokemon *child = ptr->leftLink()->rightLink();
					ptr->leftLink() = leftRotate(child, parent);
					ptr = rightRotate(ptr->leftLink(), ptr);
					lineage = 0;
				}
				else
				{ // this might happen when parent is black
				}
			}
		}
		else
		{
			lineage = 1 + insert(ptr->rightLink(), pokemon);
			if (lineage == 1)
			{ // found parent
				if (ptr->rightLink()->rightColor() != RED)
				{
					ptr->rightColor() = RED; // new child is always red, unless it has children
				}
			}
			if (lineage == 2)
			{ // found grandparent
				// if new child's parent and aunt are both red
				if (ptr->leftColor() == RED && ptr->rightColor() == RED)
				{
					ptr->leftColor() = ptr->rightColor() = BLACK;
					lineage = 0;
					// if new child's parent is red but aunt is black
				}
				else if (ptr->rightColor() == RED && ptr->rightLink()->rightColor() == RED)
				{ // this is when ptr is not grandparent to val but needs to rotate
					// right-right case, where child is right of parent and parent is right of granny
					ptr = leftRotate(ptr->rightLink(), ptr);
					lineage = 0;
				}
				else if (ptr->rightColor() == RED && ptr->rightLink()->leftColor() == RED)
				{ // this is when ptr is not grandparent to val but needs to rotate
					// right-left case, where child is right of parent and parent is left of granny
					Pokemon *parent = ptr->rightLink();
					Pokemon *child = ptr->rightLink()->leftLink();
					ptr->rightLink() = rightRotate(child, parent);
					ptr = leftRotate(ptr->rightLink(), ptr);
					lineage = 0;
				}
				else
				{ // this might happen when parent is black
				}
			}
		}
	}
	return lineage;
}

// rotate right to rebalance tree, switch colors
Pokemon *RedBlackTree::rightRotate(Pokemon *&parent, Pokemon *&grandparent)
{
	bool sib = parent->rightColor();
	bool par = grandparent->leftColor();
	parent->rightColor() = par;
	grandparent->leftColor() = sib;

	Pokemon *temp = parent;
	Pokemon *sibling = parent->rightLink();
	parent->rightLink() = grandparent;
	grandparent->leftLink() = sibling;
	return temp;
}

// rotate left to rebalance tree, switch colors
Pokemon *RedBlackTree::leftRotate(Pokemon *&parent, Pokemon *&grandparent)
{
	bool sib = parent->leftColor();
	bool par = grandparent->rightColor();
	parent->leftColor() = par;
	grandparent->rightColor() = sib;

	Pokemon *temp = parent;
	Pokemon *sibling = parent->leftLink();
	parent->leftLink() = grandparent;
	grandparent->rightLink() = sibling;
	return temp;
}

// display inorder
int RedBlackTree::displayInorder()
{
	int count = 0;
	displayInorder(root, count);
	cout << endl;
	return count;
}

// dispaly inorder
void RedBlackTree::displayInorder(Pokemon *ptr, int &count)
{
	if (ptr)
	{
		displayInorder(ptr->leftLink(), count);
		cout << ++count << ")\n";
		ptr->fullInfo();
		cout << endl;
		displayInorder(ptr->rightLink(), count);
	}
}

// display preorder
void RedBlackTree::displayPreorder()
{
	displayPreorder(root);
	cout << endl;
}

// display preorder
void RedBlackTree::displayPreorder(Pokemon *ptr)
{
	if (ptr)
	{
		ptr->fullInfo();
		cout << endl;
		displayPreorder(ptr->leftLink());
		displayPreorder(ptr->rightLink());
	}
}

// destroy tree
void RedBlackTree::destroy(Pokemon *&ptr)
{
	if (ptr)
	{
		destroy(ptr->leftLink());
		destroy(ptr->rightLink());
		delete ptr;
		ptr = NULL;
	}
}

// retrieve pokemon by name helper function
Pokemon *RedBlackTree::retrieve(const string &name)
{
	return retrieve(root, name);
}

// recursively retrieve pokemon by name
Pokemon *RedBlackTree::retrieve(Pokemon *ptr, const string &name)
{
	Pokemon *temp = NULL;
	if (ptr)
	{
		if (name == *ptr)
		{
			temp = ptr;
		}
		else if (name < *ptr)
		{
			temp = retrieve(ptr->leftLink(), name);
		}
		else
		{
			temp = retrieve(ptr->rightLink(), name);
		}
	}
	return temp;
}

// choose by pokemon by number
Pokemon *RedBlackTree::choose(const char *prompt)
{
	Pokemon *chosen = NULL;
	int count = displayInorder();
	int select = minalib::getValidateInt(prompt, 1, count);
	count = 0;
	choose(root, chosen, select, count);
	return chosen;
}

// recursively choose a pokemon by number
void RedBlackTree::choose(Pokemon *ptr, Pokemon *&chosen, int selection, int &count)
{
	if (ptr)
	{
		choose(ptr->leftLink(), chosen, selection, count);
		++count;
		if (selection == count)
		{
			chosen = ptr;
		}
		choose(ptr->rightLink(), chosen, selection, count);
	}
}

// helper function to showgrown
int RedBlackTree::showGrown()
{
	return showGrown(root);
}

// recursively call pokemon to learn new move if it has leveled up
int RedBlackTree::showGrown(Pokemon *ptr)
{
	int count = 0;
	if (ptr)
	{
		count = showGrown(ptr->leftLink());
		if (ptr->hasGrown())
		{
			ptr->learn();
			++count;
		}
		count = count + showGrown(ptr->rightLink());
	}
	return count;
}

// restore helper function
void RedBlackTree::restore()
{
	restore(root);
}

// recursively restore all pokemons
void RedBlackTree::restore(Pokemon *ptr)
{
	if (ptr)
	{
		ptr->restore();
		restore(ptr->leftLink());
		restore(ptr->rightLink());
	}
}
