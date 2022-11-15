/*
Programmer: Mina Vu
Assignment: Prog3
File name:  gym.h
Class:      CS202
Term:	    Fall 2020

This is the header file for classes Gym, RedBlack, and Kanto.
Gym class was created first aligning with the original design but could've been combined with Kanto class.
RedBlack class is the data structure for the assignment.
*/

#ifndef GYM_H
#define GYM_H

#include "pokemon.h"

class Gym {
	private:
		mstr announcement;

	public:
		Gym();//default constructor
		
		void announce(const mstr = "");//output an announcement
		void battle(Pokemon &, Pokemon &);//pokemon battle!

};

class RedBlack {
	private:
		enum {BLACK, RED};
		Pokemon* root;

		void copy(Pokemon* &, Pokemon*);//copy from one tree to another
		int height(Pokemon*);//find height of the tree
		void displayBreadth(Pokemon*, int);//display by breadth of the tree
		void displayInorder(Pokemon*, int &);//display by inorder
		void displayPreorder(Pokemon*);//display by preorder
		int insert(Pokemon* &, Pokemon*);//recursively insert a new pokemon
		Pokemon* rightRotate(Pokemon* &, Pokemon* &);//rotate right for rebalance
		Pokemon* leftRotate(Pokemon* &, Pokemon* &);//rotate left for rebalace
		void destroy(Pokemon* &);//destroy tree
		Pokemon* retrieve(Pokemon*, const mstr &);//retrieve a pokemon from the tree by name
		void choose(Pokemon*, Pokemon* &, int, int &);//select a pokemon form the tree by number
		int showGrown(Pokemon*);//find all pokemons that have leveled up
		void restore(Pokemon*);//restore all pokemons

	public:
		RedBlack();//default constructor
		RedBlack(const RedBlack &);//copy constructor
		~RedBlack();//destructor

		bool isEmpty() const;//indicate if tree is empty or not
		int height();//find height helper function
		void displayBreadth();//display by breadth helper function
		int displayInorder();//display by inorder helper function
		void displayPreorder();//display by preorder helper functon
		int insert(int, AddOnsDb*, mstr = "");//insert into tree by type indication only
		int insert(Pokemon*);//insert into tree with created pokemon
		Pokemon* retrieve(const mstr &);//retrieve pokemon by name
		Pokemon* choose(const char*);//select a pokemon with prompt
		int showGrown();//show grown helper function
		void restore();//restore helper function

		RedBlack & operator= (const RedBlack &);//= operator overload

};

class Kanto {
	private:
		AddOnsDb database;
		Gym gym;
		RedBlack backpack;
		mstr banner;

	public:
		Kanto();//default constructor
		~Kanto();//destructor
		
		void init();//initialize the game
		void start();//menu for the whole game
		mstr getBanner(const char*);//get banner from text file
		Pokemon* create(int);//create a pokemon by type indication
		mstr type(Pokemon*);//return type of pokemon as string
		void searchPokemon();//search for pokemon
		void searchItem();//search for item
		void battleSim();//pokemon battle!
		void viewPokemon();//display all pokemon in backpack
		void trainPokemon();//pokemon training
		void healPokemon();//heal all pokemon

};

#endif
