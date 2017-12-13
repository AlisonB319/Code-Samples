#include"BSTNode.h"

class BST 
{
public:
	//constructor
	BST();
	//destrucor
	~BST();
	//getter
	BSTNode *getRoot() const; 
	//setter
	void setRoot(BSTNode * const newRoot);
	//public member functions
	void print();
	void search(char letter);
	
private:
	//private member functions
	void print(BSTNode *&pTree);
	bool search(BSTNode *&pTree, char letter);


	BSTNode *mpRoot;
	void insert(BSTNode *&pTree, string morse, char character);

};

