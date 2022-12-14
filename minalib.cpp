/*
Programmer: Mina Vu
Program:	Pokemon Battle Simulation
File name:  minalib.cpp
*/

#include "minalib.h"

// get and validate user input for int
int minalib::getValidateInt(const char *prompt, int min, int max)
{
	int num = -1;
	while (num < min || num > max)
	{
		cout << prompt;
		cin >> num;
		while (!cin || num < min || num > max)
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
		while (!cin || (toupper(ch) != 'Y' && toupper(ch) != 'N'))
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

// halts program; user must hit 'Enter' to continue
void minalib::enterToContinue()
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
