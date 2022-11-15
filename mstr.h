/*
Programmer: Mina Vu
Assignment: Prog3
File name:  mstr.h
Class:      CS202
Term:	    Fall 2020

This is the header file for the classes mstr and lstr and namespace minalib.
Class mstr is my own string class, and its derived class lstr allows for long strings spanning multiple lines.
Namespace minalib is simply a container for common functions to get and validate user input.
*/

#ifndef MSTR_H
#define MSTR_H

#include <iostream>
#include <cstring>

using namespace std;

class mstr {
	protected:
		enum {MAX_CHAR = 1000};
		char* string;
		int length;

	public:
		mstr();//default constructor
		//mstr(char*);//arg constructor
		mstr(const char*);//arg constructor
		mstr(const mstr &);//copy constructor
		~mstr();//destructor

		int len();//return string length
		void getline(int = MAX_CHAR);//get one line of string input
		void getline(const char* prompt, int = MAX_CHAR);//get one line of string input
		int whatOp(const char*) const;//determine what operator for comparison
		bool compare(const char*, const char*) const;//compare member function

		mstr & operator= (const mstr &);//overload = operator

		friend ostream & operator<< (ostream &, const mstr &);//overload << operator
		friend istream & operator>> (istream &, mstr &);//overload >> operator

		friend mstr operator+ (const mstr &, const mstr &);//overload + operator
		friend mstr operator+ (const mstr &, const char*);//overload + operator
		friend mstr operator+ (const char*, const mstr &);//overload + operator

		mstr & operator+= (const mstr &);//overload += operator
		mstr & operator+= (const char*);//overload += operator

		friend bool operator== (const mstr &, const mstr &);//overload == operator
		friend bool operator== (const mstr &, const char*);//overload == operator
		friend bool operator== (const char*, const mstr &);//overload == operator

		friend bool operator!= (const mstr &, const mstr &);//overload != operator
		friend bool operator!= (const mstr &, const char*);//overload != operator
		friend bool operator!= (const char*, const mstr &);//overload != operator

		friend bool operator<= (const mstr &, const mstr &);//overload <= operator
		friend bool operator<= (const mstr &, const char*);//overload <= operator
		friend bool operator<= (const char*, const mstr &);//overload <= operator

		friend bool operator>= (const mstr &, const mstr &);//overload >= operator
		friend bool operator>= (const mstr &, const char*);//overload >= operator
		friend bool operator>= (const char*, const mstr &);//overload >= operator

		friend bool operator< (const mstr &, const mstr &);//overload < operator
		friend bool operator< (const mstr &, const char*);//overload < operator
		friend bool operator< (const char*, const mstr &);//overload < operator

		friend bool operator> (const mstr &, const mstr &);//overload > operator
		friend bool operator> (const mstr &, const char*);//overload > operator
		friend bool operator> (const char*, const mstr &);//overload > operator

};

class lstr : public mstr {
	protected:
		int size;

	public:
		lstr();//default constructor
		lstr(const lstr &);//copy constructor

		void getblock();//get user multi-line input
		void getblock(const char*);//get user multi-line input
	
};

namespace minalib {
	int getInt(const char*, int = 0, int = 1000);//get and validate user int input between min and max
	char getChar(const char*, char = 'A', char = 'Z');//get and validate user char input between min and max
	char getYesNo(const char*);//get and validate user input limit to yes and no answers
	void enterContinue();//user press enter to continue
	void clearScreen();//clear screen using newline
};

#endif
