/*
Programmer: Mina Vu
Program:	Pokemon Battle Simulation
File name:  redblacktreenode.cpp
*/

#include "redblacktreenode.h"

// default constructor
RedBlackTreeNode::RedBlackTreeNode() : lcolor(BLACK), rcolor(BLACK), left(0), right(0) {}

// destructor
RedBlackTreeNode::~RedBlackTreeNode() {}

// return color of left child
bool &RedBlackTreeNode::leftColor()
{
	return lcolor;
}

// return color of right child
bool &RedBlackTreeNode::rightColor()
{
	return rcolor;
}

// connect with left child in RB tree
RedBlackTreeNode *&RedBlackTreeNode::leftLink()
{
	return left;
}

// connect with right child in RB tree
RedBlackTreeNode *&RedBlackTreeNode::rightLink()
{
	return right;
}
