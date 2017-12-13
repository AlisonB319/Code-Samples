#include"PuttingPiecesTogether.h"



/*************************************************************
* Function: PuttingThePiecesTogether()                       *
* Date Created:7-12-17                                       *
* Date Last Modified: 7-12-17                                *
* Description: calls the program, morse code is displayed    *
* Input parameters:                                          *
* Preconditions:                                             *
* Postconditions: The morse code conversion is displayey     *
*                                                            *
*************************************************************/
void PuttingThePiecesTogether(void)
{
	fstream words("Convert.txt"); //for reading

	BST *pMorse = new BST();
	pMorse->print();

	string letter;

	while (!words.eof())
	{


		getline(words, letter);
		int firstLetter = 0; //makes sure a space is not inserted its the first character being read
		int end = 0; //will end prints, because the 3 spaces have been found

		for (int i = 0; i < letter.size(); i++)
		{

			letter[i] = toupper(letter[i]);
			
			if ((isspace(letter[i])) && (isspace(letter[i + 1])) && (isspace(letter[i + 2]))) // the next sentence is next and the text needs to go to a new line
			{
				cout << endl;
				firstLetter = 0;
				end = 1;
			}
			else if (firstLetter != 0 && end != 1)//prints a space after each character is called
			{
				cout << " ";
			}
			pMorse->search(letter[i]);
			firstLetter = 1;
		}
	}
	
	delete pMorse; //everything is finsihed, the BST can be deleted
	words.close();
}
