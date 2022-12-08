/*
Programmer: Mina Vu
Program:	Pokemon Battle Simulation
File name:  redblacktree.cpp
*/

#include "redblacktree.h"

// default constructor
RedBlackTree::RedBlackTree() : root(0) {}

// copy constructor
RedBlackTree::RedBlackTree(const RedBlackTree &source) : root(0)
{
	if (!source.root)
		return;

	copy(root, source.root);
}

// copy function copy from source root to destination root recursively
// assuming that destination root is null before processing
void RedBlackTree::copy(RedBlackTreeNode *&dstPtr, RedBlackTreeNode *srcPtr)
{
	if (!srcPtr)
		return;

	Pokemon *ptr = dynamic_cast<Pokemon *>(srcPtr);
	if (typeid(*ptr) == typeid(Pikachu))
	{
		dstPtr = new Pikachu(*(dynamic_cast<Pikachu *>(ptr)));
	}
	else if (typeid(*ptr) == typeid(Charmander))
	{
		dstPtr = new Charmander(*(dynamic_cast<Charmander *>(ptr)));
	}
	else if (typeid(*ptr) == typeid(Squirtle))
	{
		dstPtr = new Squirtle(*(dynamic_cast<Squirtle *>(ptr)));
	}
	else if (typeid(*ptr) == typeid(Bulbasaur))
	{
		dstPtr = new Bulbasaur(*(dynamic_cast<Bulbasaur *>(ptr)));
	}
	copy(dstPtr->leftLink(), srcPtr->leftLink());
	copy(dstPtr->rightLink(), srcPtr->rightLink());
}

// = operator overload
RedBlackTree &RedBlackTree::operator=(const RedBlackTree &source)
{
	if (&source == this)
		return *this;

	if (root)
		destroy(root);

	copy(root, source.root);
	return *this;
}

// destructor
RedBlackTree::~RedBlackTree()
{
	destroy(root);
}

// indicate if tree is empty or not
bool RedBlackTree::isEmpty() const
{
	return (!root) ? true : false;
}

// height function helper
int RedBlackTree::height()
{
	return height(root);
}

// recursively find height of tree
int RedBlackTree::height(RedBlackTreeNode *ptr)
{
	if (!ptr)
		return 0;

	int lheight = height(ptr->leftLink());
	int rheight = height(ptr->rightLink());
	if (lheight > rheight)
		return lheight + 1;
	else
		return rheight + 1;
}

// insert pokemon pointer
int RedBlackTree::insert(RedBlackTreeNode *pokemon)
{
	return insert(root, pokemon);
}

// insert pokemon recursively and maintain properties of a redblack tree
// this is the bulk of the work!
int RedBlackTree::insert(RedBlackTreeNode *&ptr, RedBlackTreeNode *pokemon)
{
	if (!ptr)
	{
		ptr = pokemon;
		return 0;
	}

	int lineage = 0;
	Pokemon *pPtr = dynamic_cast<Pokemon *>(ptr);
	Pokemon *pokemonPtr = dynamic_cast<Pokemon *>(pokemon);
	if (*pokemonPtr < *pPtr)
	{
		lineage = 1 + insert(ptr->leftLink(), pokemon);
		if (lineage == 1)
		{ // found parent
			if (ptr->leftLink()->leftColor() != RED)
			{
				ptr->leftColor() = RED; // new child is always red, unless it has children
			}
		}
		if (lineage == 2)
		{ // found grandparent
			// if new child's parent and aunt are both red
			if (ptr->leftColor() == RED && ptr->rightColor() == RED)
			{
				ptr->leftColor() = ptr->rightColor() = BLACK;
				lineage = 0;
				// if new child's parent is red but aunt is black
			}
			else if (ptr->leftColor() == RED && ptr->leftLink()->leftColor() == RED)
			{ // this is when ptr is not grandparent to val but needs to rotate
				// left-left case, where child is left of parent and parent is left of granny
				ptr = rightRotate(ptr->leftLink(), ptr);
				lineage = 0;
			}
			else if (ptr->leftColor() == RED && ptr->leftLink()->rightColor() == RED)
			{ // this is when ptr is not grandparent to val but needs to rotate
				// left-right case, where child is right of parent and parent is left of granny
				RedBlackTreeNode *parent = ptr->leftLink();
				RedBlackTreeNode *child = ptr->leftLink()->rightLink();
				ptr->leftLink() = leftRotate(child, parent);
				ptr = rightRotate(ptr->leftLink(), ptr);
				lineage = 0;
			}
			else
			{ // this might happen when parent is black
			}
		}
	}
	else
	{
		lineage = 1 + insert(ptr->rightLink(), pokemon);
		if (lineage == 1)
		{ // found parent
			if (ptr->rightLink()->rightColor() != RED)
			{
				ptr->rightColor() = RED; // new child is always red, unless it has children
			}
		}
		if (lineage == 2)
		{ // found grandparent
			// if new child's parent and aunt are both red
			if (ptr->leftColor() == RED && ptr->rightColor() == RED)
			{
				ptr->leftColor() = ptr->rightColor() = BLACK;
				lineage = 0;
				// if new child's parent is red but aunt is black
			}
			else if (ptr->rightColor() == RED && ptr->rightLink()->rightColor() == RED)
			{ // this is when ptr is not grandparent to val but needs to rotate
				// right-right case, where child is right of parent and parent is right of granny
				ptr = leftRotate(ptr->rightLink(), ptr);
				lineage = 0;
			}
			else if (ptr->rightColor() == RED && ptr->rightLink()->leftColor() == RED)
			{ // this is when ptr is not grandparent to val but needs to rotate
				// right-left case, where child is right of parent and parent is left of granny
				RedBlackTreeNode *parent = ptr->rightLink();
				RedBlackTreeNode *child = ptr->rightLink()->leftLink();
				ptr->rightLink() = rightRotate(child, parent);
				ptr = leftRotate(ptr->rightLink(), ptr);
				lineage = 0;
			}
			else
			{ // this might happen when parent is black
			}
		}
	}
	return lineage;
}

// rotate right to rebalance tree, switch colors
RedBlackTreeNode *RedBlackTree::rightRotate(RedBlackTreeNode *&parent, RedBlackTreeNode *&grandparent)
{
	bool sib = parent->rightColor();
	bool par = grandparent->leftColor();
	parent->rightColor() = par;
	grandparent->leftColor() = sib;

	RedBlackTreeNode *temp = parent;
	RedBlackTreeNode *sibling = parent->rightLink();
	parent->rightLink() = grandparent;
	grandparent->leftLink() = sibling;
	return temp;
}

// rotate left to rebalance tree, switch colors
RedBlackTreeNode *RedBlackTree::leftRotate(RedBlackTreeNode *&parent, RedBlackTreeNode *&grandparent)
{
	bool sib = parent->leftColor();
	bool par = grandparent->rightColor();
	parent->leftColor() = par;
	grandparent->rightColor() = sib;

	RedBlackTreeNode *temp = parent;
	RedBlackTreeNode *sibling = parent->leftLink();
	parent->leftLink() = grandparent;
	grandparent->rightLink() = sibling;
	return temp;
}

// display all inorder
int RedBlackTree::displayInorder()
{
	int count = 0;
	displayInorder(root, count);
	cout << endl;
	return count;
}

// recursively dispaly all inorder
void RedBlackTree::displayInorder(RedBlackTreeNode *ptr, int &count)
{
	if (!ptr)
		return;

	displayInorder(ptr->leftLink(), count);
	cout << ++count << ")\n";
	Pokemon *pPtr = dynamic_cast<Pokemon *>(ptr);
	pPtr->displayFullInfo();
	cout << endl;
	displayInorder(ptr->rightLink(), count);
}

// recursively destroy tree
void RedBlackTree::destroy(RedBlackTreeNode *&ptr)
{
	if (!ptr)
		return;

	destroy(ptr->leftLink());
	destroy(ptr->rightLink());
	delete ptr;
	ptr = NULL;
}

// retrieve pokemon by name helper function
RedBlackTreeNode *RedBlackTree::retrieve(const string &name)
{
	return retrieve(root, name);
}

// recursively retrieve pokemon by name
RedBlackTreeNode *RedBlackTree::retrieve(RedBlackTreeNode *ptr, const string &name)
{
	if (!ptr)
		return nullptr;

	RedBlackTreeNode *temp = NULL;
	Pokemon *pPtr = dynamic_cast<Pokemon *>(ptr);
	if (name == *pPtr)
	{
		temp = ptr;
	}
	else if (name < *pPtr)
	{
		temp = retrieve(ptr->leftLink(), name);
	}
	else
	{
		temp = retrieve(ptr->rightLink(), name);
	}

	return temp;
}

// choose by pokemon by number
RedBlackTreeNode *RedBlackTree::choose(const char *prompt)
{
	RedBlackTreeNode *chosen = NULL;
	int count = displayInorder();
	int select = minalib::getValidateInt(prompt, 1, count);
	count = 0;
	choose(root, chosen, select, count);
	return chosen;
}

// recursively choose a pokemon by number
void RedBlackTree::choose(RedBlackTreeNode *ptr, RedBlackTreeNode *&chosen, int selection, int &count)
{
	if (!ptr)
		return;

	choose(ptr->leftLink(), chosen, selection, count);
	++count;
	if (selection == count)
	{
		chosen = ptr;
	}
	choose(ptr->rightLink(), chosen, selection, count);
}

// helper function to showgrown
int RedBlackTree::showGrown()
{
	return showGrown(root);
}

// recursively call pokemon to learn new move if it has leveled up
int RedBlackTree::showGrown(RedBlackTreeNode *ptr)
{
	if (!ptr)
		return 0;

	int count = 0;
	count = showGrown(ptr->leftLink());

	Pokemon *pPtr = dynamic_cast<Pokemon *>(ptr);
	if (pPtr->hasGrown())
	{
		pPtr->learnNewAttack();
		++count;
	}

	count = count + showGrown(ptr->rightLink());

	return count;
}

// restore helper function
void RedBlackTree::restore()
{
	restore(root);
}

// recursively restore all pokemons
void RedBlackTree::restore(RedBlackTreeNode *ptr)
{
	if (!ptr)
		return;

	Pokemon *pPtr = dynamic_cast<Pokemon *>(ptr);
	pPtr->restore();
	restore(ptr->leftLink());
	restore(ptr->rightLink());
}
