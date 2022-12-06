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

	return banner;
}

// game menu
void Kanto::start()
{
	int i = 0;
	int select = 0, found = 0;
	char answer;
	Pokemon *pokemon1, *pokemon2;

	do
	{
		minalib::clearScreen();
		cout << banner << banner << banner;

		cout << "\t\t\t   Welcome to Kanto!\n\n";

		cout << "\t\t\t1) Search for wild Pokemons!\n";
		cout << "\t\t\t2) Search for Items!\n";
		cout << "\t\t\t3) Train your Pokemon!\n";
		cout << "\t\t\t4) View your Pokemons!\n";
		cout << "\t\t\t5) Battle Simulation!\n";
		cout << "\t\t\t6) Heal your Pokemons!\n";
		cout << "\t\t\t0) Quit\n";
		cout << "\n\n";
		select = minalib::getInt("What would you like to do? ", 0, 6);
		cout << endl;
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

// search for pokemon using random number generator
// user can add to backpack or not, and change name or not
void Kanto::searchPokemon()
{
	char answer;
	string type, name;
	cout << "Searching for wild Pokemons.....\n";
	int found = rand() % 3;
	if (found)
	{
		int draw = rand() % 4 + 1;
		if (draw == 1)
		{
			type = "Pikachu";
		}
		if (draw == 2)
		{
			type = "Charmander";
		}
		if (draw == 3)
		{
			type = "Squirtle";
		}
		if (draw == 4)
		{
			type = "Bulbasaur";
		}
		cout << "\nYou found a wild " << type << "!\n";
		answer = minalib::getYesNo("Would you like to catch this Pokemon? (y/n) ");
		cout << endl;
		if (toupper(answer) == 'Y')
		{
			answer = minalib::getYesNo("Do you want to give your new Pokemon a unique name? (y/n) ");
			if (toupper(answer) == 'Y')
			{
				cout << "\nWhat do you want to call your " << type << "? ";
				cin >> name;
				cin.ignore(100, '\n');
				cout << "\nGreat!\n\n";
				backpack.insert(draw, &database, name);
			}
			else
			{
				backpack.insert(draw, &database);
			}
			cout << type << " captured!\n\n";
		}
		else
		{
			cout << type << " ran away!\n\n";
		}
	}
	else
	{
		cout << "\nYou can't find any wild Pokemon.\n\n";
	}
}

// search for item by rand num generator
// give to pokemon to hold or lose
void Kanto::searchItem()
{
	char answer;
	cout << "Searching for items.....\n";
	int found = rand() % 3;
	if (found)
	{
		Items *item = dynamic_cast<Items *>(database.retrieve());
		cout << "\nYou found a " << *item << endl;
		answer = minalib::getYesNo("Do you want to give it to a Pokemon? (y/n) ");
		cout << endl;
		if (toupper(answer) == 'Y')
		{
			Pokemon *chosen = NULL;
			char ans;
			do
			{
				if (!backpack.isEmpty())
				{
					chosen = backpack.choose("Select a Pokemon to hold item: ");
					cout << endl;
					if (chosen->holding())
					{
						cout << *chosen << " is holding something already.\n";
						ans = minalib::getChar("Give item to another Pokemon? (y/n) ");
						cout << endl;
						if (toupper(ans) == 'N')
						{
							cout << "\nYou lost the item!\n\n";
							delete item;
						}
					}
					else
					{
						// chosen->hold(*item);
						*chosen += *item;
						cout << *chosen << " is now holding " << *item << endl;
						ans = 'N';
					}
				}
				else
				{
					cout << "You have no Pokemon to hold this item! You lost the item!\n\n";
					ans = 'N';
				}
			} while (toupper(ans) == 'Y');
		}
		else
		{
			cout << "\nYou lost the item!\n\n";
		}
	}
	else
	{
		cout << "\nYou can't find any item.\n\n";
	}
}

// start battle similuation having user select two pokemons
void Kanto::battleSim()
{
	char answer;
	Pokemon *pokemon1, *pokemon2;
	minalib::clearScreen();
	cout << banner << banner << banner;
	announce("\n\t\t\t   Welcome to the Pokemon Gym!\n\n");
	announce("Have your Pokemons battle each other to gain experience and level up!\n");
	answer = minalib::getYesNo("Are you ready? (y/n) ");
	cout << endl;
	if (toupper(answer) == 'Y')
	{
		cout << endl;
		if (backpack.height() > 1)
		{
			pokemon1 = backpack.choose("Select your first Pokemon for battle simulation: ");
			pokemon2 = backpack.choose("Select your second Pokemon for battle simulation: ");
			while (pokemon1 == pokemon2)
			{
				pokemon2 = backpack.choose("A Pokemon can't battle itself.\nSelect a second Pokemon for battle simulation: ");
			}
			cout << banner << banner << banner;
			battle(*pokemon1, *pokemon2);
		}
		else
		{
			cout << "You do not have enough Pokemons to simulate a battle.\nCome back again when you have at least two Pokemons.\n\n";
		}
	}
	else
	{
		cout << "Come back when you're ready!\n\n";
	}
}

// display all pokemons
void Kanto::viewPokemon()
{
	char answer;
	if (!backpack.isEmpty())
	{
		cout << "Here are your Pokemons!\n\n";
		backpack.displayInorder();
	}
	else
	{
		cout << "You don't have any Pokemon!\n\n";
	}
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
	announce("\n\t\t\t   Commence Battle Simulation!\n\n");

	cout << "\t\t\t     " << pokemon1 << " vs " << pokemon2 << endl;
	cout << endl
		 << endl
		 << endl
		 << endl
		 << endl
		 << endl;

	int turn = rand() % 2;

	while (pokemon1.state() && pokemon2.state())
	{
		switch (turn)
		{
		case 0:
			cout << pokemon1 << " attack!\n";
			pokemon1.battleStats();
			pokemon1.attack(pokemon2);
			cout << "Opponent ";
			pokemon2.battleStats();
			cout << endl
				 << endl;
			break;
		case 1:
			cout << pokemon2 << " attack!\n";
			pokemon2.battleStats();
			pokemon2.attack(pokemon1);
			cout << "Opponent ";
			pokemon1.battleStats();
			cout << endl
				 << endl;
			break;
		default:;
		}
		turn = (turn == 0) ? 1 : 0;
	}
	if (!pokemon1.state())
		cout << pokemon1 << " KO! Winner is " << pokemon2 << endl;
	if (!pokemon2.state())
		cout << pokemon2 << " KO! Winner is " << pokemon1 << endl;
	cout << endl
		 << endl;
}
