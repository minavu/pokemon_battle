/*
Programmer: Mina Vu
Assignment: Prog3
File name:  attacks.h
Class:      CS202
Term:	    Fall 2020

This is the header file for the classes Attacks, Items, and AddOnsDb.
Items class is derived from Attacks class simply for dynamic binding in AddOnsDb.
AddOnsDb require two .txt files in the specs folder to load attacks and items.
*/

#ifndef ATTACKS_H
#define ATTACKS_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include "mstr.h"

using namespace std;

class Attacks {
	private:
		mstr move;
		mstr type;
		int power;
		int accuracy;
		int pp;
		int maxPP;

	protected:
		Attacks* next;
		Attacks* prev;

	public:
		Attacks();//default constructor
		Attacks(const char*, const char*, int, int, int = 5);//arg constructor
		Attacks(mstr, mstr, int, int, int);//arg constructor
		virtual ~Attacks();//destructor

		virtual void display(ostream &) const;//display data members
		bool compareType(const Attacks &) const;//compare the type with another object's type
		bool compareType(mstr) const;//compare the type with input
		int calcDamage(const float*, const int) const;//calculate damage
		mstr mov() const;//return name for attack
		mstr typ() const;//return type for damage calculation
		int pow() const;//return power for damage calculation
		int acc() const;//return accuracy for damage calculation
		bool useAttack();//decrement pp by one to use, return false if pp is 0 for attack
		bool restore();//restore pp to maxPP
		virtual int useItem() const;//only for using dynamic binding for function in Items
		friend ostream & operator<< (ostream &, const Attacks &);//overload << operator

		Attacks* & nextLink();//get next pointer
		Attacks* & prevLink();//get prev pointer

};

class Items : public Attacks {
	private:
		mstr name;
		int hp;

	public:
		Items();//default constructor
		Items(const char*, int);//arg constructor
		Items(mstr, int);//arg constructor
		Items(const Items &);//copy constructor
		~Items();//destructor

		void display(ostream &) const;//display data members
		int useItem() const;//return hp of item for usage

};

class AddOnsDb {
	private:
		Attacks** table;
		int size;

		void init(Attacks**, Attacks**, int);//initialize table to 0, array recursion
		void copy(Attacks* &, Attacks*);//copy all table, list recursion
		void copy(Attacks**, Attacks**, Attacks**);//copy all table, array recursion
		void destroy(Attacks* &);//destroy everything, list recursion
		void destroy(Attacks**);//destroy everything, array recursion
		int insert(Attacks* &, Attacks*);//insert item, list recursion
		bool insert(Attacks**, Attacks*);//insert item, array recursion
		void display(Attacks*);//display all, list recursion
		void display(Attacks**, int = 1);//display all, array recursion
		Attacks* retrieve(Attacks*, int &, bool &, int = 0);//retrieve an attack, list recursion
		Attacks* retrieve(Attacks**, const mstr &);//retrieve an attack, array recursion
		int incrSize();//increase size of table array

	public:
		AddOnsDb();//default constructor
		AddOnsDb(const AddOnsDb &);//copy constructor
		~AddOnsDb();//destructor

		bool insert(const Attacks &);//insert attack, helper function
		bool insert(const Items &);//insert item, helper function
		void display();//display all, helper function
		Attacks* retrieve(const mstr &, const mstr = "normal");//retrieve an attack by type
		Attacks* retrieve();//retrieve an item
	
		bool addAttacks(const char*);//populate database with file of attacks
		bool addItems(const char*);//popluate database with file of items

		AddOnsDb & operator+= (const Attacks &);//+= operator overload to add an attack
		AddOnsDb & operator+= (const Items &);//+= operator overload to add an item

};

#endif
