#include"Stack.h"
#include"List.h"

Stack::Stack()
{
	maxSize = 20;
	CurrSize = 0;
	for (int i = 0; i < maxSize; i++)
	{
		mpHead[i] = "";
	}

}
string Stack::getmpHead(int location)
{
	return mpHead[location];
}

void Stack::push(const string &newItem)
{
	int posN = 0;
	int index = 0;
	

	if (isEmpty())
	{
		mpHead[0] = newItem;
		++CurrSize;
	}
	else
	{
		mpHead[CurrSize] = newItem;
		++CurrSize;
	}
}
string Stack::pop()
{
	int index = 0;
	string temp = mpHead[CurrSize];
	--CurrSize;
	return temp;
}
string Stack::peak()
{
	if (CurrSize != 0)
	{
		return mpHead[CurrSize - 1];
	}
	else
	{
		return mpHead[CurrSize];
	}
}
bool Stack::isEmpty()
{
	return CurrSize == 0;
}
int Stack::getMaxSize()
{
	return maxSize;
}
int Stack::getCurrSize()
{
	return CurrSize;
}
void Stack::setMaxSize(int newMax)
{
	maxSize = newMax;
}
void Stack::setCurrSize(int newCur)
{
	CurrSize = newCur;
}

void Stack::setmpHead(string newHead, int location)
{
	mpHead[location] = newHead;
}

void Stack::test(void)
{
	int i = 0;
	mpHead[i];
}
