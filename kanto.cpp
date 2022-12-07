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
	banner = readBannerFromFile("specs/arts/pokemon.txt");
	database.addAttacks("specs/attacks.txt");
	database.addItems("specs/items.txt");
}

// get banner from filename
string Kanto::readBannerFromFile(const char *filename)
{
	string banner, buffer;
	ifstream myfile(filename);

	if (!myfile.is_open())
		return "\n";

	while (myfile.peek() != EOF)
	{
		getline(myfile, buffer);
		banner += buffer;
		banner += "\n";
	}

	return banner + banner + banner;
}

// game menu
void Kanto::startMenuOptions()
{
	int userSelect{0};
	do
	{
		userSelect = selectFromMenu();
		switch (userSelect)
		{
		case 0:
			break;
		case 1:
			searchPokemon();
			minalib::enterToContinue();
			break;
		case 2:
			searchItem();
			minalib::enterToContinue();
			break;
		case 3:
			trainPokemon();
			minalib::enterToContinue();
			break;
		case 4:
			viewPokemon();
			minalib::enterToContinue();
			break;
		case 5:
			battleSimulation();
			minalib::enterToContinue();
			break;
		case 6:
			healPokemon();
			minalib::enterToContinue();
		default:;
		}
	} while (userSelect);
}

int Kanto::selectFromMenu()
{
	int userSelect{0};

	displayBigAnnouncement(menu);
	userSelect = minalib::getValidateInt("What would you like to do? ", 0, 6);
	cout << endl;
	return userSelect;
}

bool Kanto::winSearchLottery()
{
	return rand() % 3;
}

// search for pokemon using random number generator
// user can add to backpack or not, and change name or not
void Kanto::searchPokemon()
{
	cout << "Searching for wild Pokemons.....\n";
	if (winSearchLottery())
		return foundPokemon();
	cout << "\nYou can't find any wild Pokemon.\n\n";
}

void Kanto::foundPokemon()
{
	Pokemon *newPokemon = drawPokemonType();
	cout << "\nYou found a wild " << *newPokemon << "!\n";

	char capture = minalib::getYesNo("Would you like to catch this Pokemon? (y/n) ");
	cout << endl;
	if (toupper(capture) == 'N')
	{
		cout << *newPokemon << " ran away!\n\n";
		delete newPokemon;
		return;
	}
	renamePokemon(newPokemon);
	cout << *newPokemon << " captured!\n\n";
	backpack.insert(newPokemon);
}

Pokemon *Kanto::drawPokemonType()
{
	Pokemon *newPokemon{nullptr};
	int randomDraw = rand() % 4 + 1;
	switch (randomDraw)
	{
	case 1:
		newPokemon = new Pikachu(&database);
		break;
	case 2:
		newPokemon = new Charmander(&database);
		break;
	case 3:
		newPokemon = new Squirtle(&database);
		break;
	case 4:
		newPokemon = new Bulbasaur(&database);
		break;
	default:;
	}
	newPokemon->initialize();
	return newPokemon;
}

void Kanto::renamePokemon(Pokemon *&pokemon)
{
	string newName;
	char userInput = minalib::getYesNo("Do you want to give your new Pokemon a unique name? (y/n) ");
	if (toupper(userInput) == 'N')
		return;
	cout << "\nWhat do you want to call your " << *pokemon << "? ";
	cin >> newName;
	cin.ignore(100, '\n');
	cout << "\nGreat!\n\n";
	pokemon->changeName(newName);
}

// search for item by rand num generator
// give to pokemon to hold or lose
void Kanto::searchItem()
{
	cout << "Searching for items.....\n";
	if (winSearchLottery())
		return foundItem();
	cout << "\nYou can't find any item.\n\n";
}

void Kanto::foundItem()
{
	Items *newItem = new Items(*(dynamic_cast<Items *>(database.retrieveItem())));
	cout << "\nYou found a " << *newItem << endl;

	char answer = minalib::getYesNo("Do you want to give it to a Pokemon? (y/n) ");
	cout << endl;
	if (toupper(answer) == 'N')
	{
		cout << "\nYou lost the item!\n\n";
		delete newItem;
		return;
	}
	if (backpack.isEmpty())
	{
		cout << "You have no Pokemon to hold this item! You lost the item!\n\n";
		delete newItem;
		return;
	}

	giveItemToPokemon(newItem);
}

void Kanto::giveItemToPokemon(Items *&newItem)
{
	Pokemon *chosen{nullptr};
	char userInput{'\0'};
	do
	{
		chosen = backpack.choose("Select a Pokemon to hold item: ");
		cout << endl;
		if (!(chosen->isHoldingItem()))
		{
			*chosen += *newItem;
			cout << *chosen << " is now holding " << *newItem << endl;
			return;
		}

		cout << *chosen << " is holding something already.\n";
		userInput = minalib::getYesNo("Give item to another Pokemon? (y/n) ");
		cout << endl;
		if (toupper(userInput) == 'N')
		{
			cout << "\nYou lost the item!\n\n";
			delete newItem;
			return;
		}
	} while (toupper(userInput) == 'Y');
}

// output string
void Kanto::displayBigAnnouncement(const string message)
{
	minalib::clearScreen();
	cout << banner;
	cout << message << endl;
}

// start battle similuation having user select two pokemons
void Kanto::battleSimulation()
{
	displayBigAnnouncement(
		"\n\t\t\t   Welcome to the Pokemon Gym!\n\n"
		"Have your Pokemons battle each other to gain experience and level up!\n");

	char userInput = minalib::getYesNo("Are you ready? (y/n) ");
	cout << endl;
	if (toupper(userInput) == 'N')
	{
		cout << "Come back when you're ready!\n\n";
		return;
	}

	cout << endl;
	if (backpack.height() < 2)
	{
		cout << "You don't have enough Pokemons to simulate a battle."
			 << "\nCome back when you have at least two Pokemons.\n\n";
		return;
	}

	Pokemon *pokemon1, *pokemon2;
	choosePokemonsForBattle(pokemon1, pokemon2);
	battle(*pokemon1, *pokemon2);
}

void Kanto::choosePokemonsForBattle(Pokemon *&pokemon1, Pokemon *&pokemon2)
{
	pokemon1 = backpack.choose("Select your 1st Pokemon for battle simulation: ");
	pokemon2 = backpack.choose("Select your 2nd Pokemon for battle simulation: ");
	while (pokemon1 == pokemon2)
	{
		pokemon2 = backpack.choose("A Pokemon can't battle itself."
								   "\nSelect a 2nd Pokemon for battle simulation: ");
	}
}

// alternate turns of pokemons attacking each other until one is knocked out
void Kanto::battle(Pokemon &pokemon1, Pokemon &pokemon2)
{
	displayBigAnnouncement(
		"\n\t\t\t   Commence Battle Simulation!\n\n"
		"\t\t\t     " +
		pokemon1 + " vs " + pokemon2 + "\n\n\n\n\n\n\n");

	int turn = rand() % 2;
	while (pokemon1.isAlive() && pokemon2.isAlive())
	{
		switch (turn)
		{
		case 0:
			attack(pokemon1, pokemon2);
			break;
		case 1:
			attack(pokemon2, pokemon1);
			break;
		default:;
		}
		turn = (turn == 0) ? 1 : 0;
	}
	declareWinner(pokemon1, pokemon2);
}

void Kanto::attack(Pokemon &attacker, Pokemon &defender)
{
	cout << attacker << " attack!\n";
	attacker.displayBattleStats();
	attacker.attack(defender);
	cout << "Opponent ";
	defender.displayBattleStats();
	cout << "\n\n";
}

void Kanto::declareWinner(Pokemon &pokemon1, Pokemon &pokemon2)
{
	if (!pokemon1.isAlive())
		cout << pokemon1 << " KO! Winner is " << pokemon2 << "\n\n\n";
	if (!pokemon2.isAlive())
		cout << pokemon2 << " KO! Winner is " << pokemon1 << "\n\n\n";
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
		cout << "Your Pokemon needs to battle and gain levels before you can teach them a new move.\n";
		cout << "Be sure to visit the Battle Simulation first! Come back when your Pokemons have leveled up!\n\n";
	}
}

// heal pokemon
void Kanto::healPokemon()
{
	backpack.restore();
	cout << "\n\nYour Pokemons are all healed!\n\n";
}
