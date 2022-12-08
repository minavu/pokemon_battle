/*
Programmer: Mina Vu
Program:	Pokemon Battle Simulation
File name:  redblacktreenode.h
*/

#ifndef REDBLACKTREENODE_H
#define REDBLACKTREENODE_H

#include <iostream>
#include "addonsdb.h"

using namespace std;

// TreeNode to use for RedBlackTree
class RedBlackTreeNode
{
protected:
	enum
	{
		BLACK,
		RED
	};
	bool lcolor;
	bool rcolor;
	RedBlackTreeNode *left;
	RedBlackTreeNode *right;

public:
	RedBlackTreeNode();
	virtual ~RedBlackTreeNode();

	bool &leftColor();				// return left color for redblack tree
	bool &rightColor();				// return right color for redblack tree
	RedBlackTreeNode *&leftLink();	// return left pointer
	RedBlackTreeNode *&rightLink(); // return right pointer
};

#endif
