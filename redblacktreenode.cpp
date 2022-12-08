/*
Programmer: Mina Vu
Assignment: Prog3
File name:  redblacktreenode.cpp
Class:      CS202
Term:	    Fall 2020

This file contains the implementations for class RedBlackTreeNode.
*/

#include "redblacktreenode.h"

RedBlackTreeNode::RedBlackTreeNode() : lcolor(BLACK), rcolor(BLACK), left(0), right(0) {}

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
