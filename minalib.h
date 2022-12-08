/*
Programmer: Mina Vu
Program:	Pokemon Battle Simulation
File name:  minalib.h
*/

#ifndef MINALIB_H
#define MINALIB_H

#include <iostream>
#include <cctype>

using namespace std;

// useful functions for Pokemon Battle Simulation
namespace minalib
{
	int getValidateInt(const char *prompt, int min = 0, int max = 1000);
	char getYesNo(const char *prompt);
	void enterToContinue();
	void clearScreen();
};

#endif
