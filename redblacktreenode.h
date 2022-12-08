/*
Programmer: Mina Vu
Assignment: Prog3
File name:  redblacktreenode.h
Class:      CS202
Term:	    Fall 2020

This is the header file for the class RedBlackTreeNode.
*/

#ifndef REDBLACKTREENODE_H
#define REDBLACKTREENODE_H

#include <iostream>
#include "addonsdb.h"

using namespace std;

class RedBlackTreeNode {
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

		bool &leftColor();	   // return left color for redblack tree
		bool &rightColor();	   // return right color for redblack tree
		RedBlackTreeNode *&leftLink();  // return left pointer
		RedBlackTreeNode *&rightLink(); // return right pointer

};

#endif
