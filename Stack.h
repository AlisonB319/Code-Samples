
#pragma once
#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

class Stack
{
public:
	Stack();
	
	int getMaxSize();
	int getCurrSize();
	string getmpHead(int location);

	void setMaxSize(int newMax);
	void setCurrSize(int newCur);
	void setmpHead(string newHead, int location);

	string peak();
	string pop();
	void push(const string &newItem);
	bool isEmpty();
	void test(void);


private:
	int maxSize;
	int CurrSize;
	string mpHead[20];

};


#endif
