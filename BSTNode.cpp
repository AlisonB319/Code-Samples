#include"BSTNode.h"

//constructor
BSTNode::BSTNode(char character, string newMorse)
{
	mLetter = character;
	mMorse = newMorse;
	mpLeft = nullptr;
	mpRight = nullptr;
}

//destructor
BSTNode::~BSTNode()
{
	//cout << "inside the destructor Node" << endl;
	delete  mpLeft;
	delete mpRight;
}

//getters
char BSTNode::getLetter()
{
	return mLetter;
}
string BSTNode::getMorse()
{
	return mMorse;
}
BSTNode *& BSTNode::getLeft()
{
	return mpLeft;
}
BSTNode *& BSTNode::getRight()
{
	return mpRight;
}

//setters
void BSTNode::setLetter(const char newLetter)
{
	mLetter = newLetter;
}
void BSTNode::setMorse(const string newMorse)
{
	mMorse = newMorse;
}
void BSTNode::setLeft(BSTNode * const newLeft)
{
	mpLeft = newLeft;
}
void BSTNode::setRight(BSTNode * const newRight)
{
	mpRight = newRight;
}
