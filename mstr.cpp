/*
Programmer: Mina Vu
Assignment: Prog3
File name:  mstr.cpp
Class:      CS202
Term:	    Fall 2020

This file contains the implementations outlined in the header file.
Implementations are for classes mstr and lstr and for namespace minalib.
More information below.
*/

#include "mstr.h"

//default constructor
mstr::mstr() : string(0), length(0) {}

//arg constructor
mstr::mstr(const char* newString) : string(0), length(0) {
	length = strlen(newString);
	string = new char[length + 1];
	strcpy(string, newString);
}

//copy constructor
mstr::mstr(const mstr & source) : string(0), length(0) {
	if (&source != this) {
		length = source.length;
		string = new char[source.length + 1];
		strcpy(string, source.string);
	}
}

//destructor
mstr::~mstr() {
	delete [] string;
	string = NULL;
}

//return string length
int mstr::len() {
	return length;
}

//mimic getline function allowing for user to indicate size of string
void mstr::getline(int size) {
	char buffer[size];
	cin.getline(buffer, size);
	if (string) {
		delete [] string;
	}
	length = strlen(buffer);
	string = new char[length + 1];
	strcpy(string, buffer);
}

//mimic getline function allowing for user to indicate size of string with a prompt
void mstr::getline(const char* prompt, int size) {
	char buffer[size];
	cout << prompt;
	cin.getline(buffer, size);
	if (string) {
		delete [] string;
	}
	length = strlen(buffer);
	string = new char[length + 1];
	strcpy(string, buffer);
}

//return int indicating which operator char* is
int mstr::whatOp(const char* op) const {
	char ops[][3] = {"==", "!=", "<=", ">=", "<", ">"};
	int i = 0;
	while (strcmp(op, ops[i]) != 0) {
		++i;
	}
	return i;
}

//return bool after comparing strings
//args are string to compare and operator
bool mstr::compare(const char* str, const char* op) const {
	bool answer = false;
	int what = whatOp(op);
	switch (what) {
		case 0:
			if (strcmp(string, str) == 0) {
				answer = true;
			}
			break;
		case 1:
			if (strcmp(string, str) != 0) {
				answer = true;
			}
			break;
		case 2:
			if (strcmp(string, str) == 0 || strcmp(string, str) < 0) {
				answer = true;
			}
			break;
		case 3:
			if (strcmp(string, str) == 0 || strcmp(string, str) > 0) {
				answer = true;
			}
			break;
		case 4:
			if (strcmp(string, str) < 0) {
				answer = true;
			}
			break;
		case 5:
			if (strcmp(string, str) > 0) {
				answer = true;
			}
			break;
		default:;
	}
	return answer;
}

//= operator overload
mstr & mstr::operator= (const mstr & source) {
	if (&source != this) {
		if (string) {
			delete [] string;
		}
		length = source.length;
		string = new char[length + 1];
		strcpy(string, source.string);
	}
	return *this;
}

//<< operator overload
ostream & operator<< (ostream & os, const mstr & str) {
	os << str.string;
	return os;
}

//>> operator overload
istream & operator>> (istream & is, mstr & str) {
	char buffer[str.MAX_CHAR];
	is >> buffer;
	if (str.string) {
		delete [] str.string;
	}
	str.length = strlen(buffer);
	str.string = new char[str.length + 1];
	strcpy(str.string, buffer);
	return is;
}

//+ operator overload
mstr operator+ (const mstr & str1, const mstr & str2) {
	mstr temp;
	temp.length = str1.length + str2.length;
	temp.string = new char[temp.length + 1];
	strcpy(temp.string, str1.string);
	strcat(temp.string, str2.string);
	return temp;
}

//+ operatory overload
mstr operator+ (const mstr & str1, const char* str2) {
	mstr temp;
	temp.length = str1.length + strlen(str2);
	temp.string = new char[temp.length + 1];
	strcpy(temp.string, str1.string);
	strcat(temp.string, str2);
	return temp;
}

//+ operatory overload
mstr operator+ (const char* str1, const mstr & str2) {
	mstr temp;
	temp.length = strlen(str1) + str2.length;
	temp.string = new char[temp.length + 1];
	strcpy(temp.string, str1);
	strcat(temp.string, str2.string);
	return temp;
	
}

//+= operator overload
mstr & mstr::operator+= (const mstr & str) {
	length += str.length;
	char* temp = new char[length + 1];
	strcpy(temp, string);
	strcat(temp, str.string);
	if (string) {
		delete [] string;
	}
	string = temp;
	return *this;
}

//+= operator overload
mstr & mstr::operator+= (const char* str) {
	length += strlen(str);
	char* temp = new char[length + 1];
	strcpy(temp, string);
	strcat(temp, str);
	if (string) {
		delete [] string;
	}
	string = temp;
	return *this;
}

//== operator overload
bool operator== (const mstr & str1, const mstr & str2) {
	return str1.compare(str2.string, "==");
}

//== operator overload
bool operator== (const mstr & str1, const char* str2) {
	return str1.compare(str2, "==");
}

//== operator overload
bool operator== (const char* str1, const mstr & str2) {
	return str2.compare(str1, "==");
}

//!= operator overload
bool operator!= (const mstr & str1, const mstr & str2) {
	return str1.compare(str2.string, "!=");
}

//!= operator overload
bool operator!= (const mstr & str1, const char* str2) {
	return str1.compare(str2, "!=");
}

//!= operator overload
bool operator!= (const char* str1, const mstr & str2) {
	return str2.compare(str1, "!=");
}

//<= operator overload
bool operator<= (const mstr & str1, const mstr & str2) {
	return str1.compare(str2.string, "<=");
}

//<= operator overload
bool operator<= (const mstr & str1, const char* str2) {
	return str1.compare(str2, "<=");
}

//<= operator overload
bool operator<= (const char* str1, const mstr & str2) {
	return str2.compare(str1, ">=");
}

//>= operator overload
bool operator>= (const mstr & str1, const mstr & str2) {
	return str1.compare(str2.string, ">=");
}

//>= operator overload
bool operator>= (const mstr & str1, const char* str2) {
	return str1.compare(str2, ">=");
}

//>= operator overload
bool operator>= (const char* str1, const mstr & str2) {
	return str2.compare(str1, "<=");
}

//< operator overload
bool operator< (const mstr & str1, const mstr & str2) {
	return str1.compare(str2.string, "<");
}

//< operator overload
bool operator< (const mstr & str1, const char* str2) {
	return str1.compare(str2, "<");
}

//< operator overload
bool operator< (const char* str1, const mstr & str2) {
	return str2.compare(str1, ">");
}

//> operator overload
bool operator> (const mstr & str1, const mstr & str2) {
	return str1.compare(str2.string, ">");
}

//> operator overload
bool operator> (const mstr & str1, const char* str2) {
	return str1.compare(str2, ">");
}

//> operator overload
bool operator> (const char* str1, const mstr & str2) {
	return str2.compare(str1, "<");
}










//default constructor
lstr::lstr() : size(MAX_CHAR) {}

//copy constructor
lstr::lstr(const lstr & source) : mstr(source), size(0) {
	size = source.size;
}

//function allowing user to enter multiple lines of words and storing it in string
void lstr::getblock() {
	char* buffer = new char[size];
	char add[size];
	length = 0;
	
	cout << "--Type (.) on new line to end--\n";
	cin.getline(buffer, size);
	length += strlen(buffer);
	while (cin.peek() != '.') {
		cin.getline(add, size);
		++length += strlen(add);
		if (length > size - 200) {
			char* temp = new char[size += MAX_CHAR];
			strcpy(temp, buffer);
			delete [] buffer;
			buffer = temp;	
		}
		strcat(buffer, "\n");
		strcat(buffer, add);
	}
	cin.ignore(size, '\n');
	if (string) {
		delete [] string;
	}
	string = buffer;
}

//allows user to enter multiple lines to a string with prompt
void lstr::getblock(const char* prompt) {
	cout << prompt;
	getblock();
}








//get and validate user input for int
int minalib::getInt(const char* prompt, int min, int max) {
	int num = 0;
	cout << prompt;
	cin >> num;
	while (!cin) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << prompt;
		cin >> num;
	}
	while (num < min || num > max) {
		cout << prompt;
		cin >> num;
		while (!cin) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << prompt;
			cin >> num;
		}
	}
	cin.ignore(100, '\n');
	return num;
}

//get and validate user input for char
char minalib::getChar(const char* prompt, char min, char max) {
	char ch;
	cout << prompt;
	cin >> ch;
	while (!cin) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << prompt;
		cin >> ch;
	}
	while (toupper(ch) < min || toupper(ch) > max) {
		cout << prompt;
		cin >> ch;
		while (!cin) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << prompt;
			cin >> ch;
		}
	}
	cin.ignore(100, '\n');
	return ch;
}

//get and validate user input for yes/no answers
char minalib::getYesNo(const char* prompt) {
	char ch;
	cout << prompt;
	cin >> ch;
	while (!cin) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << prompt;
		cin >> ch;
	}
	while (toupper(ch) != 'Y' && toupper(ch) != 'N') {
		cout << prompt;
		cin >> ch;
		while (!cin) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << prompt;
			cin >> ch;
		}
	}
	cin.ignore(100, '\n');
	return ch;
}

//user must hit 'Enter' to continue, halts program
void minalib::enterContinue() {
	cout << "\nPress Enter to continue ";
	cin.ignore(100, '\n');
}

//clear the screen using newline characters
void minalib::clearScreen() {
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}


