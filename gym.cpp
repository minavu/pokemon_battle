/*
Programmer: Mina Vu
Assignment: Prog3
File name:  gym.cpp
Class:      CS202
Term:	    Fall 2020

This file contains all the implementations for classes Kanto, Gym, and RedBlack.
Some functions were later not used because better ideas materialized.
Function information below.
*/

#include "gym.h"

//default constructor
Kanto::Kanto() : banner("") {}

//destructor
Kanto::~Kanto() {}

//get input from text files
void Kanto::init() {
	banner = getBanner("specs/arts/pokemon.txt");
	database.addAttacks("specs/attacks.txt");
	database.addItems("specs/items.txt");
}

//game menu
void Kanto::start() {
	int i = 0;
	int select = 0, found = 0;
	char answer;
	Pokemon* pokemon1, * pokemon2;

	do {
		minalib::clearScreen();
		if (banner != "") {
			cout << banner << banner << banner;
		}

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
		switch (select) {
			case 0: break;
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

//create a pokemon by type, not used in the end
/*
Pokemon* Kanto::create(int type) {
	Pokemon* temp;
	if (type == 1) {
		temp = new Pikachu(&database);
	}
	if (type == 2) {
		temp = new Charmander(&database);
	}
	if (type == 3) {
		temp = new Squirtle(&database);
	}
	if (type == 4) {
		temp = new Bulbasaur(&database);
	}
	temp->initialize();
	return temp;
}

//return pokemon type in string, not used in the end
mstr Kanto::type(Pokemon* pokemon) {
	mstr name;
	if (typeid(*pokemon) == typeid(Pikachu)) {
		name = "Pikachu";
	}
	if (typeid(*pokemon) == typeid(Charmander)) {
		name = "Charmander";
	}
	if (typeid(*pokemon) == typeid(Squirtle)) {
		name = "Squirtle";
	}
	if (typeid(*pokemon) == typeid(Bulbasaur)) {
		name = "Bulbasaur";
	}
	return name;
}
*/

//search for pokemon using random number generator
//user can add to backpack or not, and change name or not
void Kanto::searchPokemon() {
	char answer;
	mstr type, name;
	cout << "Searching for wild Pokemons.....\n";
	int found = rand() % 3;
	if (found) {
		int draw = rand() % 4 + 1;
		if (draw == 1) {
			type = "Pikachu";
		}
		if (draw == 2) {
			type = "Charmander";
		}
		if (draw == 3) {
			type = "Squirtle";
		}
		if (draw == 4) {
			type = "Bulbasaur";
		}
		//Pokemon* wild = create(draw);
		cout << "\nYou found a wild " << type << "!\n";
		//wild->battleStats();
		answer = minalib::getYesNo("Would you like to catch this Pokemon? (y/n) ");
		cout << endl;
		if (toupper(answer) == 'Y') {
			answer = minalib::getYesNo("Do you want to give your new Pokemon a unique name? (y/n) ");
			if (toupper(answer) == 'Y') {
				cout << "\nWhat do you want to call your " << type << "? ";
				//cin >> *wild;
				cin >> name;
				cin.ignore(100, '\n');
				cout << "\nGreat!\n\n";
				backpack.insert(draw, &database, name);
			} else {
				backpack.insert(draw, &database);
			}
			cout << type << " captured!\n\n";
		} else {
			cout << type << " ran away!\n\n";
			//delete wild;
		}
	} else {
		cout << "\nYou can't find any wild Pokemon.\n\n";
	}
}

//search for item by rand num generator
//give to pokemon to hold or lose
void Kanto::searchItem() {
	char answer;
	cout << "Searching for items.....\n";
	int found = rand() % 3;
	if (found) {
		Items* item = dynamic_cast<Items*>(database.retrieve());
		cout << "\nYou found a " << *item << endl;
		answer = minalib::getYesNo("Do you want to give it to a Pokemon? (y/n) ");
		cout << endl;
		if (toupper(answer) == 'Y') {
			Pokemon* chosen = NULL;
			char ans;
			do {
				if (!backpack.isEmpty()) {
					chosen = backpack.choose("Select a Pokemon to hold item: ");
					cout << endl;
					if (chosen->holding()) {
						cout << *chosen << " is holding something already.\n";
						ans = minalib::getChar("Give item to another Pokemon? (y/n) ");
						cout << endl;
						if (toupper(ans) == 'N') {
							cout << "\nYou lost the item!\n\n";
							delete item;
						}
					} else {
						//chosen->hold(*item);
						*chosen += *item;
						cout << *chosen << " is now holding " << *item << endl;
						ans = 'N';
					}
				} else {
					cout << "You have no Pokemon to hold this item! You lost the item!\n\n";
					ans = 'N';
				}
			} while (toupper(ans) == 'Y');
		} else {
			cout << "\nYou lost the item!\n\n";
		}
	} else {
		cout << "\nYou can't find any item.\n\n";
	}
}

//start battle similuation having user select two pokemons
void Kanto::battleSim() {
	char answer;
	Pokemon* pokemon1, * pokemon2;
	minalib::clearScreen();
	cout << banner << banner << banner;
	gym.announce("\n\t\t\t   Welcome to the Pokemon Gym!\n\n");
	gym.announce("Have your Pokemons battle each other to gain experience and level up!\n");
	answer = minalib::getYesNo("Are you ready? (y/n) ");
	cout << endl;
	if (toupper(answer) == 'Y') {
		cout << endl;
		if (backpack.height() > 1) {
			pokemon1 = backpack.choose("Select your first Pokemon for battle simulation: ");
			pokemon2 = backpack.choose("Select your second Pokemon for battle simulation: ");
			while (pokemon1 == pokemon2) {
				pokemon2 = backpack.choose("A Pokemon can't battle itself.\nSelect a second Pokemon for battle simulation: ");
			}
			cout << banner << banner << banner;
			gym.battle(*pokemon1, *pokemon2);
		} else {
			cout << "You do not have enough Pokemons to simulate a battle.\nCome back again when you have at least two Pokemons.\n\n";
		}
	} else {
		cout << "Come back when you're ready!\n\n";
	}
}

//display all pokemons
void Kanto::viewPokemon() {
	char answer;
	if (!backpack.isEmpty()) {
		cout << "Here are your Pokemons!\n\n";
		backpack.displayInorder();
	} else {
		cout << "You don't have any Pokemon!\n\n";
	}
}

//train pokemon
void Kanto::trainPokemon() {
	if (!backpack.showGrown()) {
		cout << "Your Pokemon needs to battle an gain levels before you can teach them a new move.\n";
		cout << "Be sure to visit the Battle Simulation first! Come back when your Pokemon has leveled up!\n\n";
	}
}

//heal pokemon
void Kanto::healPokemon() {
	backpack.restore();
	cout << "\n\nYour Pokemons are all healed!\n\n";
}

//get file input
mstr Kanto::getBanner(const char* file) {
	mstr string = "";
	char buffer[100];

	ifstream myfile(file);
	if (myfile.is_open()) {
		while (myfile.peek() != EOF) {
			myfile.get(buffer, 100);
			myfile.ignore(100, '\n');
			string += buffer;
			string += "\n";
		}
	}
	
	return string;
}












//default constructor
Gym::Gym() {}

//output string
void Gym::announce(const mstr string) {
	if (string != "") {
		cout << string << endl;
	}
}

//alternate turns of pokemons attacking each other until one is knocked out
void Gym::battle(Pokemon & pokemon1, Pokemon & pokemon2) {
	announce("\n\t\t\t   Commence Battle Simulation!\n\n");

	cout << "\t\t\t     " << pokemon1 << " vs " << pokemon2 << endl;
	cout << endl << endl << endl << endl << endl << endl;

	int turn = rand() % 2;

	while (pokemon1.state() && pokemon2.state()) {
		switch (turn) {
			case 0:
				cout << pokemon1 << " attack!\n";
				pokemon1.battleStats();
				pokemon1.attack(pokemon2);
				cout << "Opponent ";
				pokemon2.battleStats();
				cout << endl << endl;
				break;
			case 1:
				cout << pokemon2 << " attack!\n";
				pokemon2.battleStats();
				pokemon2.attack(pokemon1);
				cout << "Opponent ";
				pokemon1.battleStats();
				cout << endl << endl;
				break;
			default:;
		}
		turn = (turn == 0) ? 1 : 0;
	}
	if (!pokemon1.state()) cout << pokemon1 << " KO! Winner is " << pokemon2 << endl;
	if (!pokemon2.state()) cout << pokemon2 << " KO! Winner is " << pokemon1 << endl;
	cout << endl << endl;
}










//default constructor
RedBlack::RedBlack() : root(0) {}

//copy constructor
RedBlack::RedBlack(const RedBlack & source) : root(0) {
	if (source.root) {
		copy(root, source.root);
	}
}

//copy function copy from source root to destination root recursively
//assuming that destination root is null before processing
void RedBlack::copy(Pokemon* & dstPtr, Pokemon* srcPtr) {
	if (srcPtr) {
		if (typeid(*srcPtr) == typeid(Pikachu)) {
			dstPtr = new Pikachu(*(dynamic_cast<Pikachu*>(srcPtr)));
		} else if (typeid(*srcPtr) == typeid(Charmander)) {
			dstPtr = new Charmander(*(dynamic_cast<Charmander*>(srcPtr)));
		} else if (typeid(*srcPtr) == typeid(Squirtle)) {
			dstPtr = new Squirtle(*(dynamic_cast<Squirtle*>(srcPtr)));
		} else if (typeid(*srcPtr) == typeid(Bulbasaur)) {
			dstPtr = new Bulbasaur(*(dynamic_cast<Bulbasaur*>(srcPtr)));
		}
		copy(dstPtr->leftLink(), srcPtr->leftLink());
		copy(dstPtr->rightLink(), srcPtr->rightLink());
	}
}

//= operator overload
RedBlack & RedBlack::operator= (const RedBlack & source) {
	if (&source != this) {
		if (root) {
			destroy(root);
		}
		copy(root, source.root);
	}
	return *this;
}

//destructor
RedBlack::~RedBlack() {
	destroy(root);
}

//indicate if tree is empty or not
bool RedBlack::isEmpty() const {
	return (!root) ? true : false;
}

//height function helper
int RedBlack::height() {
	return height(root);
}

//recursively find height of tree
int RedBlack::height(Pokemon* ptr) {
    int level = 0;
    if (ptr) {
        int lheight = height(ptr->leftLink());
        int rheight = height(ptr->rightLink());
        if (lheight > rheight) {
            level = lheight + 1;
        } else {
            level = rheight + 1;
        }
    }
    return level;
}

//display tree by breadth
void RedBlack::displayBreadth() {
    int h = height(root);
    for (int i = 1; i <= h; ++i) {
        cout << "Level " << i << ":  ";
        displayBreadth(root, i);
        cout << endl;
    }
}

//recursively display tree by breadth
void RedBlack::displayBreadth(Pokemon* ptr, int level) {
    if (ptr) {
        if (level == 1) {
            cout << *ptr << ", colors are: " << ptr->leftColor() << "/" << ptr->rightColor() << "\t";
        } else {
            displayBreadth(ptr->leftLink(), level - 1);
            displayBreadth(ptr->rightLink(), level - 1);
        }
    }
}

//insert pokemon pointer 
int RedBlack::insert(Pokemon* pokemon) {
	return insert(root, pokemon);
}

//insert pokemon by type indication
int RedBlack::insert(int draw, AddOnsDb* database, mstr name) {
	Pokemon* toAdd = NULL;
	if (draw == 1) {
		if (name != "") {
			toAdd = new Pikachu(database, name);
		} else {
			toAdd = new Pikachu(database);
		}
	}
	if (draw == 2) {
		if (name != "") {
			toAdd = new Charmander(database, name);
		} else {
			toAdd = new Charmander(database);
		}
	}
	if (draw == 3) {
		if (name != "") {
			toAdd = new Squirtle(database, name);
		} else {
			toAdd = new Squirtle(database);
		}
	}
	if (draw == 4) {
		if (name != "") {
			toAdd = new Bulbasaur(database, name);
		} else {
			toAdd = new Bulbasaur(database);
		}
	}
	toAdd->initialize();
	return insert(root, toAdd);
}

//insert pokemon recursively and maintain properties of a redblack tree
//this is the bulk of the work!
int RedBlack::insert(Pokemon* & ptr, Pokemon* pokemon) {
    int lineage = 0;
    if (!ptr) {
        ptr = pokemon;
    } else {
        if (*pokemon < *ptr) {
            lineage = 1 + insert(ptr->leftLink(), pokemon);
            if (lineage == 1) {//found parent
                if (ptr->leftLink()->leftColor() != RED) {
                    ptr->leftColor() = RED;//new child is always red, unless it has children
                }
            }
            if (lineage == 2) {//found grandparent
                //if new child's parent and aunt are both red
                if (ptr->leftColor() == RED && ptr->rightColor() == RED) {
                    ptr->leftColor() = ptr->rightColor() = BLACK;
                    lineage = 0;
                //if new child's parent is red but aunt is black
                } else if (ptr->leftColor() == RED && ptr->leftLink()->leftColor() == RED) {//this is when ptr is not grandparent to val but needs to rotate
                    //left-left case, where child is left of parent and parent is left of granny
                    ptr = rightRotate(ptr->leftLink(), ptr);
                    lineage = 0;
                } else if (ptr->leftColor() == RED && ptr->leftLink()->rightColor() == RED) {//this is when ptr is not grandparent to val but needs to rotate
                    //left-right case, where child is right of parent and parent is left of granny
                    Pokemon* parent = ptr->leftLink();
                    Pokemon* child = ptr->leftLink()->rightLink();
                    ptr->leftLink() = leftRotate(child, parent);
                    ptr = rightRotate(ptr->leftLink(), ptr);
                    lineage = 0;
                } else {//this might happen when parent is black
                }
            }
        } else {
            lineage = 1 + insert(ptr->rightLink(), pokemon);
            if (lineage == 1) {//found parent
                if (ptr->rightLink()->rightColor() != RED) {
                    ptr->rightColor() = RED;//new child is always red, unless it has children
                }
            }
            if (lineage == 2) {//found grandparent
                //if new child's parent and aunt are both red
                if (ptr->leftColor() == RED && ptr->rightColor() == RED) {
                    ptr->leftColor() = ptr->rightColor() = BLACK;
                    lineage = 0;
                //if new child's parent is red but aunt is black
                } else if (ptr->rightColor() == RED && ptr->rightLink()->rightColor() == RED) {//this is when ptr is not grandparent to val but needs to rotate
                    //right-right case, where child is right of parent and parent is right of granny
                    ptr = leftRotate(ptr->rightLink(), ptr);
                    lineage = 0;
                } else if (ptr->rightColor() == RED && ptr->rightLink()->leftColor() == RED) {//this is when ptr is not grandparent to val but needs to rotate
                    //right-left case, where child is right of parent and parent is left of granny
                    Pokemon* parent = ptr->rightLink();
                    Pokemon* child = ptr->rightLink()->leftLink();
                    ptr->rightLink() = rightRotate(child, parent);
                    ptr = leftRotate(ptr->rightLink(), ptr);
                    lineage = 0;
                } else {//this might happen when parent is black
                }
            }
        }
    }
    return lineage;
}

//rotate right to rebalance tree, switch colors
Pokemon* RedBlack::rightRotate(Pokemon* & parent, Pokemon* & grandparent) {
    bool sib = parent->rightColor();
    bool par = grandparent->leftColor();
    parent->rightColor() = par;
    grandparent->leftColor() = sib;

    Pokemon* temp = parent;
    Pokemon* sibling = parent->rightLink();
    parent->rightLink() = grandparent;
    grandparent->leftLink() = sibling;
    return temp;
}

//rotate left to rebalance tree, switch colors
Pokemon* RedBlack::leftRotate(Pokemon* & parent, Pokemon* & grandparent) {
    bool sib = parent->leftColor();
    bool par = grandparent->rightColor();
    parent->leftColor() = par;
    grandparent->rightColor() = sib;

    Pokemon* temp = parent;
    Pokemon* sibling = parent->leftLink();
    parent->leftLink() = grandparent;
    grandparent->rightLink() = sibling;
    return temp;
}

//display inorder
int RedBlack::displayInorder() {
	int count = 0;
        displayInorder(root, count);
	cout << endl;
	return count;
}

//dispaly inorder
void RedBlack::displayInorder(Pokemon* ptr, int & count) {
    if (ptr) {
        displayInorder(ptr->leftLink(), count);
	cout << ++count << ")\n";
	ptr->fullInfo();
	cout << endl;
        displayInorder(ptr->rightLink(), count);
    }
}

//display preorder
void RedBlack::displayPreorder() {
	displayPreorder(root);
	cout << endl;
}

//display preorder
void RedBlack::displayPreorder(Pokemon* ptr) {
	if (ptr) {
		ptr->fullInfo();
		cout << endl;
		displayPreorder(ptr->leftLink());
		displayPreorder(ptr->rightLink());
	}
}

//destroy tree
void RedBlack::destroy(Pokemon* & ptr) {
	if (ptr) {
		destroy(ptr->leftLink());
		destroy(ptr->rightLink());
		delete ptr;
		ptr = NULL;
	}
}

//retrieve pokemon by name helper function
Pokemon* RedBlack::retrieve(const mstr & name) {
	return retrieve(root, name);
}

//recursively retrieve pokemon by name
Pokemon* RedBlack::retrieve(Pokemon* ptr, const mstr & name) {
	Pokemon* temp = NULL;
	if (ptr) {
		if (name == *ptr) {
			temp = ptr;
		} else if (name < *ptr) {
			temp = retrieve(ptr->leftLink(), name);
		} else {
			temp = retrieve(ptr->rightLink(), name);
		}
	}
	return temp;
}

//choose by pokemon by number
Pokemon* RedBlack::choose(const char* prompt) {
	Pokemon* chosen = NULL;
	int count = displayInorder();
	int select = minalib::getInt(prompt, 1, count);
	count = 0;
	choose(root, chosen, select, count);
	return chosen;
}

//recursively choose a pokemon by number
void RedBlack::choose(Pokemon* ptr, Pokemon* & chosen, int selection, int & count) {
	if (ptr) {
		choose(ptr->leftLink(), chosen, selection, count);
		++count;
		if (selection == count) {
			chosen = ptr;
		}
		choose(ptr->rightLink(), chosen, selection, count);
	}
}

//helper function to showgrown
int RedBlack::showGrown() {
	return showGrown(root);
}

//recursively call pokemon to learn new move if it has leveled up
int RedBlack::showGrown(Pokemon* ptr) {
	int count = 0;
	if (ptr) {
		count = showGrown(ptr->leftLink());
		if (ptr->hasGrown()) {
			ptr->learn();
			++count;
		}
		count = count + showGrown(ptr->rightLink());
	}
	return count;
}

//restore helper function
void RedBlack::restore() {
	restore(root);
}

//recursively restore all pokemons
void RedBlack::restore(Pokemon* ptr) {
	if (ptr) {
		ptr->restore();
		restore(ptr->leftLink());
		restore(ptr->rightLink());
	}
}





