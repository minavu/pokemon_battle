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
#include <cctype>

using namespace std;

namespace minalib
{
	int getValidateInt(const char *prompt, int min = 0, int max = 1000); // get and validate user int input between min and max
	char getYesNo(const char *prompt);									 // get and validate user input limit to yes and no answers
	void enterToContinue();												 // user press enter to continue
	void clearScreen();													 // clear screen using newline
};

#endif
