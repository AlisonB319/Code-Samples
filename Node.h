#include"Stack.h"

class Node : public Stack
{
	friend class List;
public:
	Node();
	~Node();
	Node(const Node &copy);


	int getRecord();
	int getID();
	string getName();
	int getUnit();
	string getProgram();
	string getLevel();
	int getNumAbs();
	string getEmail();
	string getMissedAbs(int location);

	void setRecord(int newRecord);
	void setID(int newID);
	void setName(string newName);
	void setUnits(int newUnits);
	void setProgram(string newProgram);
	void setLevel(string newLevel);
	void setNumAbs(int newNumAbs);
	void setEmail(string newEmail);
	void setMissedAns(string newDate, int location);

	Node operator=(Node &rhs);
	
protected:
	int mRecordNum;
	int mIDNum;
	string mName;
	int mUnits;
	string mProgram;
	string mLevel;
	int mNumAbs;
	string mEmail;
	Stack mMissedAbs;

};

fstream & operator << (fstream &lhs, Node &rhs);
ifstream & operator >> (ifstream &lhs, Node &rhs);
