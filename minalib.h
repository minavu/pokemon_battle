/*
Programmer: Mina Vu
Assignment: Prog3
File name:  minalib.h
Class:      CS202
Term:	    Fall 2020

This is the header file for the namespace minalib.
Namespace minalib is a container for common functions to get and validate user input.
*/

#ifndef MINALIB_H
#define MINALIB_H

#include <iostream>
#include <cstring>

using namespace std;

namespace minalib
{
	int getInt(const char *, int = 0, int = 1000);		// get and validate user int input between min and max
	char getChar(const char *, char = 'A', char = 'Z'); // get and validate user char input between min and max
	char getYesNo(const char *);						// get and validate user input limit to yes and no answers
	void enterContinue();								// user press enter to continue
	void clearScreen();									// clear screen using newline
};

#endif
