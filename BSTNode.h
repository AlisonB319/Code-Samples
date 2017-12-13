#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
//#include"BST.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::fstream;
using std::ifstream;
using std::getline;
using std::vector;

class BSTNode
{
public: 
	BSTNode(char character, string newMorse);

	~BSTNode();

	void setLetter(const char newLetter);
	void setMorse(const string newMorse);
	void setLeft(BSTNode * const newLeft);
	void setRight(BSTNode * const newRight);

	char getLetter();
	string getMorse();
	BSTNode *& getLeft();
	BSTNode *& getRight();

private:
	char mLetter;
	string mMorse;
	BSTNode *mpLeft;
	BSTNode *mpRight;

};

