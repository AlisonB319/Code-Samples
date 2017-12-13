#include"Node.h"
#include"Stack.h"
//container class
class List : protected Node
{
	friend class Node;

public:
	List();

	Node NodeContainer[20];

	void retrieveData(void);
	void writeToMasterList(void);
	void markAbs(void);
	void loadMasterList(void);
	void report1(void);
	void report2(void);
	void editAbs(void);

private:
	int NodeContainerCurSize;
};

string getTime(void);
