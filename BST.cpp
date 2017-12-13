#include"BST.h"


//getter
BSTNode *BST::getRoot() const
{
	return mpRoot;
}

//setter
void BST::setRoot(BSTNode * const newRoot)
{
	mpRoot = newRoot;
}

//destructor
BST::~BST()
{
	//cout << "inside the destructor BST" << endl;
	delete mpRoot;

}

//construtor
/*
Creates the nodes for the tree, it opens the file and passes the information into insert
*/
BST::BST()
{
	fstream morseCode("MorseTable.txt"); //for reading
	mpRoot = nullptr;


	while (!morseCode.eof())
	{
		char letter[2] = { "\0" };
		string sequence[2];
		int i = 0;

		morseCode >> letter[i];
		morseCode >> sequence[i];

		insert(mpRoot, sequence[i], letter[i]);
		i++;
	}
	morseCode.close();

}

/*************************************************************
* Function: insert()                                         *
* Date Created:7-10-17                                       *
* Date Last Modified: 7-10-17                                *
* Description: inserts a node in to the BST                  *                                                     
* Input parameters: the Node, and the data for the string and*
* character                                                  *
* Preconditions:  The node must be created                   *
* Postconditions: A node with information is complete        *
*                                                            *
*************************************************************/
void BST::insert(BSTNode *&pTree, string morse, char character)
{
	if (pTree == NULL)
	{
		BSTNode *pMem = new BSTNode(character, morse);
		pTree = pMem;
	}
	else if (character < (pTree)->getLetter())
	{
		insert((pTree)->getLeft(), morse, character);
	}
	else if (character > (pTree)->getLetter())
	{
		insert((pTree)->getRight(), morse, character);
	}
}

//public call for print
void BST::print()
{
	print(mpRoot);
}

//preorder private print function
void BST::print(BSTNode *&pTree)
{
	if (pTree != nullptr)
	{

		print(pTree->getLeft());
		cout << pTree->getLetter() << " " << pTree->getMorse() << endl; // processed
		print(pTree->getRight());
	}

}

//public search function
void BST::search(char letter)
{
	search(mpRoot, letter);
}

//private search function
bool BST::search(BSTNode *&pTree, char letter)
{

	if (pTree == nullptr)
	{
		return false;
	}
	if (pTree->getLetter() == letter)
	{
		cout << pTree->getMorse();
		return true;
	}
	else if (pTree->getLetter() < letter)
	{
		return search(pTree->getRight(), letter);
	}
	else //(pTree->getLetter() > letter)
	{
		return search(pTree->getLeft(), letter);
	}

}
