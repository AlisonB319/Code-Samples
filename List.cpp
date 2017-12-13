#include"List.h"

List::List()
{
	NodeContainerCurSize = 0;
}

/*************************************************************
* Function: retrieveData()                                   *
* Date Created:7-17-17                                       *
* Date Last Modified: 7-17-17                                *
* Description: inputes the classlist.csv File                *
* Input parameters:                                          *
* Preconditions:                                             *
* Postconditions:                                            *
*                                                            *
*************************************************************/
void List::retrieveData(void)
{
	fstream InputFile("classList.csv"); //for reading

	string tempString;

	std::getline(InputFile, tempString);


	int i = 0;
	while (!InputFile.eof())
	{
		string tempstring, tempUnits, tempRecords, tempID, tempName, tempNameF, tempNameL, tempEmail, tempProgram, tempLevel;

		std::getline(InputFile, tempRecords, ',');
		std::getline(InputFile, tempID, ',');
		std::getline(InputFile, tempNameF, ',');
		std::getline(InputFile, tempNameL, ',');

		tempNameF = tempNameF + " ";
		tempName = tempNameF + tempNameL;

		std::getline(InputFile, tempEmail, ',');
		std::getline(InputFile, tempUnits, ',');
		std::getline(InputFile, tempProgram, ',');
		std::getline(InputFile, tempLevel);


		mRecordNum = std::stoi(tempRecords);
		mIDNum = std::stoi(tempID);
		mName = tempName;
		mEmail = tempEmail;
		if (tempUnits != "AU")
		{
			mUnits = std::stoi(tempUnits);
		}
		else
		{
			mUnits = 0;
		}
		mProgram = tempProgram;
		mLevel = tempLevel;

		NodeContainer[i].setRecord(mRecordNum);
		NodeContainer[i].setID(mIDNum);
		NodeContainer[i].setName(mName);
		NodeContainer[i].setEmail(mEmail);
		NodeContainer[i].setUnits(mUnits);
		NodeContainer[i].setProgram(mProgram);
		NodeContainer[i].setLevel(mLevel);
		NodeContainerCurSize++;
		i++;
	}
}

/*************************************************************
* Function: marksAbs()                                       *
* Date Created:7-17-17                                       *
* Date Last Modified: 7-17-17                                *
* Description: Allows absences to be added to the stack      *
* Input parameters:                                          *
* Preconditions:                                             *
* Postconditions: The stack now has dates                    *
*                                                            *
*************************************************************/
void List::markAbs(void)
{
	char answer = '\0';
	string temp = "";
	for (int i = 0; i < NodeContainerCurSize; i++)
	{
		cout << "Would you List to mark an Absense for " << NodeContainer[i].getName() << endl;
		cout << "Please enter 'y' for yes and 'n' for no" << endl;
		cin >> answer;
		//answer = 'y';
		if (answer == 'y')
		{

			int curTotalAbs = NodeContainer[i].getNumAbs();

			string date1 = getTime();

			NodeContainer[i].mMissedAbs.push(date1);
			curTotalAbs++;
			NodeContainer[i].mMissedAbs.setCurrSize(curTotalAbs);
			NodeContainer[i].setNumAbs(curTotalAbs);
			cout << endl;
		}
		else
		{
			cout << endl;
		}
	}
}

/*************************************************************
* Function: getTime()                                       *
* Date Created:7-17-17                                       *
* Date Last Modified: 7-18-17                                *
* Description: gets the date from the computer               *
* Input parameters:                                          *
* Preconditions:                                             *
* Postconditions:                                            *
*                                                            *
*************************************************************/
string getTime(void)
{
	time_t currentTime;
	struct tm *localTime;
	time(&currentTime);
	localTime = localtime(&currentTime);

	int Day = localTime->tm_mday;
	int Month = localTime->tm_mon + 1;
	int Year = localTime->tm_year + 1900;
	int Hour = localTime->tm_hour;
	int Min = localTime->tm_min;
	int Sec = localTime->tm_sec;

	string day = std::to_string(Day);
	string month = std::to_string(Month);
	string year = std::to_string(Year);
	string hour = std::to_string(Hour);
	string min = std::to_string(Min);

	string date = month + "-" + day + "-" + year;
	return date;
}

/*************************************************************
* Function: writeToMasterList()                              *
* Date Created:7-17-17                                       *
* Date Last Modified: 7-18-17                                *
* Description: Writes all of the nodes data to the master    *
* list                                                       *
* Input parameters:                                          *
* Preconditions:                                             *
* Postconditions: The master list is updated                 *
*                                                            *
*************************************************************/
void List::writeToMasterList(void) // store
{
	ofstream masterList("MasterList.txt"); // for writing
	int loop = 0;
	for (int i = 0; i < NodeContainerCurSize; i++)
	{
		string abs = "";

		if (NodeContainer[i].getUnit() == 0)
		{
			masterList << NodeContainer[i].getRecord() << " " << NodeContainer[i].getID() << " " << NodeContainer[i].getName() << " " << NodeContainer[i].getEmail() << " " << "AU" << " " << NodeContainer[i].getProgram() << " " << NodeContainer[i].getLevel();
			int temp = NodeContainer[i].mMissedAbs.getCurrSize();
			for (int k = 0; k <= temp; k++)
			{
				if (NodeContainer[i].mMissedAbs.getmpHead(k) != "")
				{
					masterList << " " << NodeContainer[i].mMissedAbs.getmpHead(k);
				}
			}
			if (i != NodeContainerCurSize - 1) //elimate the endl on the file
			{
				masterList << endl;
			}
		}
		else
		{
			masterList << NodeContainer[i].getRecord() << " " << NodeContainer[i].getID() << " " << 
				NodeContainer[i].getName() << " " << NodeContainer[i].getEmail() << " " << NodeContainer[i].getUnit() << " " << 
				NodeContainer[i].getProgram() << " " << NodeContainer[i].getLevel();
			
			int temp = NodeContainer[i].mMissedAbs.getCurrSize();
			for (int k = 0; k <= temp; k++)
			{
				if (NodeContainer[i].mMissedAbs.getmpHead(k) != "")
				{
					masterList << " " << NodeContainer[i].mMissedAbs.getmpHead(k);
				}
			}
			if (i != NodeContainerCurSize - 1) //elimate the endl on the file
			{
				masterList << endl;
			}
		}
	}
	masterList << " ."; //fixes infinite loop in loadMasterList
	masterList.close();
}

/*************************************************************
* Function: loadToMasterList()                               *
* Date Created:7-17-17                                       *
* Date Last Modified: 7-18-17                                *
* Description: loads all of the absense data from the master *
* list                                                       *
* Input parameters:                                          *
* Preconditions:                                             *
* Postconditions: The Nodes have previsous absense data      *
*                                                            *
*************************************************************/
void List::loadMasterList(void)
{
	fstream masterList("MasterList.txt"); // for reading
	int vBreak = 0, testRec = 0, size = 0, i = 0;
	char infiniteLoopCheck = 'a';
	while (!masterList.eof())
	{
		vBreak = 0;
		string tempstring, tempUnits, tempRecords, tempID, tempName, tempNameF, tempNameL, tempEmail, tempProgram, tempLevel, tempAbs, temp;

		if (testRec == 0)
		{
			masterList >> tempRecords >> tempID >> tempNameL >> tempNameF >> tempEmail >> tempUnits >> tempProgram >> tempLevel;
		}
		else
		{
			masterList >> tempID >> tempNameL >> tempNameF >> tempEmail >> tempUnits >> tempProgram >> tempLevel; //there was no abs the previsous loop so tempRecords is already stored

		}

		tempName = tempNameL + " " + tempNameF;

		while (vBreak == 0) //vBreak will break the while loop once all of the past Abs are inserted into the file
		{
			if (NodeContainer[i].getName() == tempName)
			{
				masterList >> temp; //causing an infinite loop
				size = temp.length();

				if (size > 3 && infiniteLoopCheck != '.')
				{
					int curTotalAbs = NodeContainer[i].getNumAbs();
					curTotalAbs++;
					NodeContainer[i].mMissedAbs.push(temp);
					NodeContainer[i].mMissedAbs.setCurrSize(curTotalAbs);
					NodeContainer[i].setNumAbs(curTotalAbs);
					testRec = 1; 
					infiniteLoopCheck = masterList.get();
				}
				else
				{
					vBreak = 1;
				}
			}
			else
			{
				vBreak = 1;
				testRec = 0;
			}
		}
		i++;
	}
}

/*************************************************************
* Function: report1()                                        *
* Date Created:7-18-17                                       *
* Date Last Modified: 7-18-17                                *
* Description: Writes the student names and most recent      *
* absense                                                    *
* Input parameters:                                          *
* Preconditions:                                             *
* Postconditions: Report1.txt is updated                     *
*                                                            *
*************************************************************/
void List::report1(void)
{
	//all students and most recent absense
	ofstream Report1("Report1.txt"); // for writing

	for (int i = 0; i < NodeContainerCurSize; i++)
	{
		Report1 << NodeContainer[i].getName() << " " << NodeContainer[i].mMissedAbs.peak() << endl;
	}
}

/*************************************************************
* Function: report2()                                        *
* Date Created:7-18-17                                       *
* Date Last Modified: 7-18-17                                *
* Description: Writes the student names and all  recent      *
* absense                                                    *
* Input parameters:                                          *
* Preconditions:                                             *
* Postconditions: Report2.txt is updated                     *
*                                                            *
*************************************************************/
void List::report2(void)
{
	ofstream Report2("Report2.txt"); // for writing

	int AbsMax = 0;
	cout << "For Report 2, How many absences does the student need to have in order to write to the file: " << endl;
	cin >> AbsMax;
	for (int i = 0; i < NodeContainerCurSize; i++)
	{
		if (NodeContainer[i].mMissedAbs.getCurrSize() >= AbsMax)
		{
			Report2 << NodeContainer[i].getName() << " ";
			for (int k = 0; k < NodeContainer[i].mMissedAbs.getCurrSize(); k++)
			{
				Report2 << NodeContainer[i].mMissedAbs.getmpHead(k) << " ";
			}
			Report2 << endl;
		}
	}
}

/*************************************************************
* Function: editAbs()                                        *
* Date Created:7-18-17                                       *
* Date Last Modified: 7-18-17                                *
* Description: Edits or delets an absense                    *
* Input parameters:                                          *
* Preconditions: absense must exsist                         *
* Postconditions: The node's information changes             *
*                                                            *
*************************************************************/
void List::editAbs(void)
{
	int searchID = 0, searchSlot = 0, location = 0;
	int match = 0;
	string newDate = "";
	cout << "Please enter a 4 digit ID number: " << endl;
	cin >> searchID;

	for (int i = 0; i < NodeContainerCurSize; i++)
	{
		if (searchID == NodeContainer[i].getID())
		{
			cout << "1) Replace Absence" << endl << "2) Delete Absense" << endl;
			cin >> match;
			location = i;
		}
	}

	if (match == 1)
	{
		for (int k = 0; k < NodeContainer[location].mMissedAbs.getCurrSize(); k++)
		{
			cout << k+1 << " "  << NodeContainer[location].mMissedAbs.getmpHead(k) << " ";
		}
		cout << endl;
		cout << "Please enter the slot you wish to change!" << endl;
		cin >> searchSlot;

		cout << "Please enter a new date DD-MM-YYYY: " << endl;
		cin >> newDate;

		NodeContainer[location].mMissedAbs.setmpHead(newDate, searchSlot-1);
		cout << "The absences has been edited" << endl;
	}
	else if (match == 2)
	{
		string temparray[20];
		for (int k = 0; k < NodeContainer[location].mMissedAbs.getCurrSize(); k++)
		{
			cout << k + 1 << " " << NodeContainer[location].mMissedAbs.getmpHead(k) << " ";
			temparray[k] = NodeContainer[location].mMissedAbs.getmpHead(k);
			NodeContainer[location].mMissedAbs.setmpHead("", k); //makes it blank so it can be edited
		}
		cout << endl;
		cout << "Please enter the slot you wish to remove!" << endl;
		cin >> searchSlot;


		for (int i = 19; i > NodeContainer[location].getCurrSize(); i--)
		{
			if (temparray[i] != "")
			{
				string tempInsert = temparray[i];
				NodeContainer[location].mMissedAbs.push(tempInsert); //makes it blank so it can be edited
			}
		}

		cout << "The Item was removed" << endl;
	}
	else 
	{
		cout << "Entered ID was not found" << endl;
	} 

}
