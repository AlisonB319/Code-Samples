/*******************************************************************************
* Programmer: Alison Burgess                                                   *
* Class: CptS 122; Lab Section 1                                               *
* Programming Assignment: PA 6c                                                *
* Date: 7-18-17                                                                *
*                                                                              *
* Description: It is a program that will import a class list, and the user     *
* has the option to change the attendence of the students                      *
*                                                                              *
* Relevant Formulas: Refer to each function definition.                        *
*                                                                              *
* Format of record in input file ():                        int RecordNum      *
*                                                           int ID             *
*															string Name        *
*															string Email       *
*															int credits        *
*															int Major          *
*															int Level          *
* NOTE: FOR THE MASTER lIST THE LAST LINE MUST HAVE A "' '." (SPACE PERIOD)    *
* IN ORDER FOR AN INFINITE LOOP TO NOT OCCUR- OR USING YOUR INPUTTED FILE      *
* RUN THE WRITETOMASTERLIST() FUNCTION AND IT WILL ADD IT                      *                                                     *
********************************************************************************/

#include"List.h"

int main(void)
{

	List p1;
	int choice = 0;
	char temp = '\0';
	cout << "Welcome to Attendence Tracker!" << endl;
	while (choice != 7)
	{
		do
		{
			cout << "1) " << "Import Course List" << endl;
			cout << "2) " << "Load master list" << endl;
			cout << "3) " << "Store master list" << endl;
			cout << "4) " << "Mark absences" << endl;
			cout << "5) " << "Edit absences" << endl;
			cout << "6) " << "Generate report" << endl;
			cout << "7) " << "Exit" << endl;
			cin >> choice;
		} while (choice < 1 || choice > 7);
		if (choice == 1)
		{
			p1.retrieveData();

			cout << "The class List has been imported" << endl;
			cout << "Press enter to continue";
			cin.ignore();
			cin.get();
		}
		else if (choice == 2)
		{
			p1.retrieveData();
			p1.loadMasterList();
			cout << "The master list has been Loaded" << endl;
			cout << "Press enter to continue";
			cin.ignore();
			cin.get();
		}
		else if (choice == 3)
		{
			p1.writeToMasterList();
			cout << endl << "The master list has been stored" << endl;
			cout << "Press enter to continue";
			cin.ignore();
			cin.get();
		}
		else if (choice == 4)
		{
			p1.markAbs();
			cout << "All absences have been marked" << endl;
			cout << "Press enter to continue";
			cin.ignore();
			cin.get();
		}
		else if (choice == 5)
		{
			p1.editAbs();
			cout << "Press enter to continue";
			cin.ignore();
			cin.get();
		}
		else if (choice == 6)
		{
			p1.report1();
			p1.report2();
			cout << "The reports have been generated" << endl;
			cout << "Press enter to continue";
			cin.ignore();
			cin.get();
		}
		else if (choice == 7)
		{
			cout << "Attendance Finished" << endl;
			p1.writeToMasterList();
		}
	}


	return 0;
}

