#include"Node.h"

Node::Node() 
{
	mRecordNum = 0;
	mIDNum = 0;
	mName = "";
	mUnits = 0;
	mProgram = "";
	mLevel = "";
	mEmail = "";
	mNumAbs = 0;
	mMissedAbs;
}
Node::~Node()
{
	//cout << "inside Node destructor" << endl;
}
Node::Node(const Node &copy)
{
	mRecordNum = copy.mRecordNum;
	mIDNum = copy.mIDNum;
	mName = copy.mName;
	mUnits = copy.mUnits;
	mProgram = copy.mProgram;
	mLevel = copy.mLevel;
	mNumAbs = copy.mNumAbs;
	mEmail = copy.mEmail;
	mMissedAbs;
}
//getters
int Node::getRecord()
{
	return mRecordNum;
}
int Node::getID()
{
	return mIDNum;
}
string Node::getName()
{
	return mName;
}
int Node::getUnit()
{
	return mUnits;
}
string Node::getProgram()
{
	return mProgram;
}
string Node::getLevel()
{
	return mLevel;
}
int Node::getNumAbs()
{
	return mNumAbs;
}
string Node::getEmail()
{
	return mEmail;
}
string Node::getMissedAbs(int location)
{
	return mMissedAbs.getmpHead(location);
}
//setters
void Node::setRecord(int newRecord)
{
	mRecordNum = newRecord;
}
void Node::setID(int newID)
{
	mIDNum = newID;
}
void Node::setName(string newName)
{
	mName = newName;
}
void Node::setUnits(int newUnits)
{
	mUnits = newUnits;
}
void Node::setProgram(string newProgram)
{
	mProgram = newProgram;
}
void Node::setLevel(string newLevel)
{
	mLevel = newLevel;
}
void Node::setNumAbs(int newNumAbs)
{
	mNumAbs = newNumAbs;
}
void Node::setEmail(string newEmail)
{
	mEmail = newEmail;
}
void Node::setMissedAns(string newDate, int location)
{
	mMissedAbs.setmpHead(newDate, location);
	
}


//= overloaded assignment operators
Node Node::operator=(Node &rhs)
{
	mRecordNum = rhs.mRecordNum;
	mIDNum = rhs.mIDNum;
	mName = rhs.mName;
	mUnits = rhs.mUnits;
	mProgram = rhs.mProgram;
	mLevel = rhs.mLevel;
	mNumAbs = rhs.mNumAbs;
	mEmail = rhs.mEmail;

	return *this;
}

//file overloaded assignment operators
fstream & operator << (fstream &lhs, Node &rhs)
{
	lhs << rhs.getRecord() << rhs.getID() << rhs.getName() << rhs.getUnit() << rhs.getProgram() << rhs.getLevel();
	rhs.getNumAbs(), rhs.getEmail();
	return lhs;
}
ifstream & operator >> (ifstream &lhs, Node &rhs)
{
	string name, program, level, email;
	int RecordNum, IDnum, Units, NumAbs;

	lhs >> IDnum >> name >> program >> level >> email >> RecordNum >> Units >> NumAbs;
	rhs.setID(IDnum);
	rhs.setName(name);
	rhs.setProgram(program);
	rhs.setLevel(level);
	rhs.setEmail(email);
	rhs.setRecord(RecordNum);
	rhs.setUnits(Units);
	rhs.setNumAbs(NumAbs);

	return lhs;

}
