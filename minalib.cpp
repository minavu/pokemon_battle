/*
Programmer: Mina Vu
Assignment: Prog3
File name:  minalib.cpp
Class:      CS202
Term:	    Fall 2020

This file contains the implementations outlined in the header file.
Implementations are for namespace minalib.
*/

#include "minalib.h"

// get and validate user input for int
int minalib::getInt(const char *prompt, int min, int max)
{
	int num = -1;
	while (num < min || num > max)
	{
		cout << prompt;
		cin >> num;
		while (!cin)
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << prompt;
			cin >> num;
		}
	}
	cin.ignore(100, '\n');
	return num;
}

// get and validate user input for yes/no answers
char minalib::getYesNo(const char *prompt)
{
	char ch = '\0';
	while (toupper(ch) != 'Y' && toupper(ch) != 'N')
	{
		cout << prompt;
		cin >> ch;
		while (!cin)
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << prompt;
			cin >> ch;
		}
	}
	cin.ignore(100, '\n');
	return ch;
}

// user must hit 'Enter' to continue, halts program
void minalib::enterContinue()
{
	cout << "\nPress Enter to continue ";
	cin.ignore(100, '\n');
}

// clear the screen using newline characters
void minalib::clearScreen()
{
	for (int i{0}; i < 4; ++i)
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}
