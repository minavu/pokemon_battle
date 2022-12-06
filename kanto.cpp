/*
Programmer: Mina Vu
Assignment: Prog3
File name:  kanto.cpp
Class:      CS202
Term:	    Fall 2020

This file contains all the implementations for class Kanto.
Function information below.
*/

#include "kanto.h"

// get input from text files
void Kanto::init()
{
	menu = 
		"\t\t\t   Welcome to Kanto!\n\n"
		"\t\t\t1) Search for wild Pokemons!\n"
		"\t\t\t2) Search for Items!\n"
		"\t\t\t3) Train your Pokemon!\n"
		"\t\t\t4) View your Pokemons!\n"
		"\t\t\t5) Battle Simulation!\n"
		"\t\t\t6) Heal your Pokemons!\n"
		"\t\t\t0) Quit\n"
		"\n\n";
	banner = getBanner("specs/arts/pokemon.txt");
	database.addAttacks("specs/attacks.txt");
	database.addItems("specs/items.txt");
}

// get banner from file
string Kanto::getBanner(const char *file)
{
	string banner, buffer;
	ifstream myfile(file);

	if (!myfile.is_open())
		return "\n";

	while (myfile.peek() != EOF)
	{
		getline(myfile, buffer);
		banner += buffer;
		banner += "\n";
	}

	banner += banner + banner;

	return banner;
}

// game menu
void Kanto::start()
{
	int select {0};

	do
	{
		select = selectFromMenu();
		switch (select)
		{
		case 0:
			break;
		case 1:
			searchPokemon();
			minalib::enterContinue();
			break;
		case 2:
			searchItem();
			minalib::enterContinue();
			break;
		case 3:
			trainPokemon();
			minalib::enterContinue();
			break;
		case 4:
			viewPokemon();
			minalib::enterContinue();
			break;
		case 5:
			battleSim();
			minalib::enterContinue();
			break;
		case 6:
			healPokemon();
			minalib::enterContinue();
		default:;
		}
	} while (select);
}

int Kanto::selectFromMenu() {
	int select {0};

	minalib::clearScreen();

	cout << banner;
	cout << menu;

	select = minalib::getInt("What would you like to do? ", 0, 6);
	cout << endl;
	return select;
}

// search for pokemon using random number generator
// user can add to backpack or not, and change name or not
void Kanto::searchPokemon()
{
	char capture, rename;
	string type, name;
	cout << "Searching for wild Pokemons.....\n";
	int found = rand() % 3;
	if (!found)
	{
		cout << "\nYou can't find any wild Pokemon.\n\n";
		return;
	}

	type = drawPokemon();
	cout << "\nYou found a wild " << type << "!\n";
	capture = minalib::getYesNo("Would you like to catch this Pokemon? (y/n) ");
	cout << endl;
	if (toupper(capture) == 'N')
	{
		cout << type << " ran away!\n\n";
		return;
	}

	rename = minalib::getYesNo("Do you want to give your new Pokemon a unique name? (y/n) ");
	if (toupper(rename) == 'N')
	{
		backpack.insert(type, &database);
		cout << type << " captured!\n\n";
		return;
	}

	cout << "\nWhat do you want to call your " << type << "? ";
	cin >> name;
	cin.ignore(100, '\n');
	cout << "\nGreat!\n\n";
	backpack.insert(type, &database, name);
}

string Kanto::drawPokemon() {
	int draw = rand() % 4 + 1;
	switch (draw) {
		case 1:
			return "Pikachu";
			break;
		case 2:
			return "Charmander";
			break;
		case 3:
			return "Squirtle";
			break;
		case 4:
			return "Bulbasaur";
			break;
		default:
			return "";
	}
}

// search for item by rand num generator
// give to pokemon to hold or lose
void Kanto::searchItem()
{
	char answer;
	cout << "Searching for items.....\n";
	int found = rand() % 3;
	if (!found)
	{
		cout << "\nYou can't find any item.\n\n";
		return;
	}

	Items *item = dynamic_cast<Items *>(database.retrieve());
	cout << "\nYou found a " << *item << endl;
	answer = minalib::getYesNo("Do you want to give it to a Pokemon? (y/n) ");
	cout << endl;
	if (toupper(answer) == 'N')
	{
		cout << "\nYou lost the item!\n\n";
		delete item;
		return;
	}

	if (backpack.isEmpty())
	{
		cout << "You have no Pokemon to hold this item! You lost the item!\n\n";
		delete item;
		return;
	}

	Pokemon *chosen = NULL;
	char ans;
	do
	{
		chosen = backpack.choose("Select a Pokemon to hold item: ");
		cout << endl;
		if (!(chosen->holding()))
		{
			*chosen += *item;
			cout << *chosen << " is now holding " << *item << endl;
			return;
		}

		cout << *chosen << " is holding something already.\n";
		ans = minalib::getChar("Give item to another Pokemon? (y/n) ");
		cout << endl;
		if (toupper(ans) == 'N')
		{
			cout << "\nYou lost the item!\n\n";
			delete item;
			return;
		}
	} while (toupper(ans) == 'Y');
}

// start battle similuation having user select two pokemons
void Kanto::battleSim()
{
	char answer;
	Pokemon *pokemon1, *pokemon2;
	minalib::clearScreen();
	cout << banner;
	announce("\n\t\t\t   Welcome to the Pokemon Gym!\n\n");
	announce("Have your Pokemons battle each other to gain experience and level up!\n");
	answer = minalib::getYesNo("Are you ready? (y/n) ");
	cout << endl;
	if (toupper(answer) == 'N')
	{
		cout << "Come back when you're ready!\n\n";
		return;
	}

	cout << endl;
	if (backpack.height() < 2)
	{
		cout << "You do not have enough Pokemons to simulate a battle.\nCome back again when you have at least two Pokemons.\n\n";
		return;
	}

	pokemon1 = backpack.choose("Select your first Pokemon for battle simulation: ");
	pokemon2 = backpack.choose("Select your second Pokemon for battle simulation: ");
	while (pokemon1 == pokemon2)
	{
		pokemon2 = backpack.choose("A Pokemon can't battle itself.\nSelect a second Pokemon for battle simulation: ");
	}
	battle(*pokemon1, *pokemon2);
}

// output string
void Kanto::announce(const string string)
{
	if (string != "")
	{
		cout << string << endl;
	}
}

// alternate turns of pokemons attacking each other until one is knocked out
void Kanto::battle(Pokemon &pokemon1, Pokemon &pokemon2)
{
	minalib::clearScreen();
	cout << banner;
	announce("\n\t\t\t   Commence Battle Simulation!\n\n");

	cout << "\t\t\t     " << pokemon1 << " vs " << pokemon2;
	cout << "\n\n\n\n\n\n\n";

	int turn = rand() % 2;
	while (pokemon1.state() && pokemon2.state())
	{
		switch (turn)
		{
		case 0:
			attack(pokemon1, pokemon2)
			break;
		case 1:
			attack(pokemon2, pokemon1)
			break;
		default:;
		}
		turn = (turn == 0) ? 1 : 0;
	}
	declareWinner(pokemon1, pokemon2);
}

void Kanto::attack(Pokemon & attacker, Pokemon & defender) {
	cout << attacker << " attack!\n";
	attacker.battleStats();
	attacker.attack(defender);
	cout << "Opponent ";
	defender.battleStats();
	cout << endl << endl;
}

void Kanto::declareWinner(Pokemon & pokemon1, Pokemon & pokemon2) {
	if (!pokemon1.state())
		cout << pokemon1 << " KO! Winner is " << pokemon2 << endl;
	if (!pokemon2.state())
		cout << pokemon2 << " KO! Winner is " << pokemon1 << endl;
	cout << endl << endl;
}

// display all pokemons
void Kanto::viewPokemon()
{
	if (backpack.isEmpty())
	{
		cout << "You don't have any Pokemon!\n\n";
		return;
	}

	cout << "Here are your Pokemons!\n\n";
	backpack.displayInorder();
}

// train pokemon
void Kanto::trainPokemon()
{
	if (!backpack.showGrown())
	{
		cout << "Your Pokemon needs to battle an gain levels before you can teach them a new move.\n";
		cout << "Be sure to visit the Battle Simulation first! Come back when your Pokemon has leveled up!\n\n";
	}
}

// heal pokemon
void Kanto::healPokemon()
{
	backpack.restore();
	cout << "\n\nYour Pokemons are all healed!\n\n";
}
