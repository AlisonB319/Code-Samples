Skip to content
Enterprise
This repository
Search
Pull requests
Issues
Gist
 @aburges1
 Sign out
 Watch 1
  Star 0  Fork 0 CptS223-2017Fall/cs223-aburges1 Private
 Code  Issues 0  Pull requests 0  Projects 0  Wiki  Pulse  Graphs
Branch: PA3 Find file Copy pathcs223-aburges1/PA3/dictionary.h
e787121  on Oct 29
@aburges1 aburges1 Some print statement changes
2 contributors @aburges1 @acrandal
RawBlameHistory     
304 lines (265 sloc)  10.2 KB
/*
*  dictionary.h -- A hash-based dictionary for searching definitions
*   Copyright 2017 - Aaron S. Crandall <acrandal@gmail.com>
*/

#ifndef __DICT_H
#define __DICT_H

#include "hashtable.h"
#include "word.h"
#include "json.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

using json = nlohmann::json;

class Dictionary
{

private:
	Hashtable<string, Word> _dict;  // Primary dictionary store

	void parseline(string line) {
		//cout << " [d] Parsing line: " << line << endl;
        //cout << "TEST : " << line << "\n";

		//unsigned long length = line.size();
		if (line.find('\"'))
		{
			std::replace(line.begin(), line.end(), '\"', '\0');
		}

		for (unsigned int i = 0; i < line.size(); i++)
		{
			line[i] = tolower(line[i]);
		}
		//cout << "NEW TEST : " << line << "\n";
		string input = line.substr(0, line.find(' '));


		if (input == "help")
		{
			cout << "'add'    : Add or update a word and it's definiton\n";
			cout <<	"'remove' : Remove a given word\n";
			cout <<	"'define' : Enter a word and recieve the definition\n";
			cout <<	"'load'   : Load in a JSON file of dictionary words\n";
			cout <<	"'unload' : Remove words from a given JSON file\n";
			cout <<	"'size'   : Print out the current number of words in the dictionary\n";
			cout << "'clear   : Remove all words from the dictionary\n";
			cout <<	"'print'  : Print out all words, or give a maximum number\n";
			cout <<	"'random' : Will print out one random word\n";
			cout <<	"'quit'   : Quit the user interface and shut down\n";
		}


		if (input == "add")
		{
			string lineWithOutInput = line.substr(input.size()+1, line.size());
			string word = lineWithOutInput.substr(0, lineWithOutInput.find(' '));
			string defin = line.substr(word.size() + input.size() +2 , line.size() + 1);

			word.erase (std::remove (word.begin(), word.end(), '\0'), word.end());

			Word entry;
			entry.myword = word;
			entry.definition = defin;

			_dict.insert(word, entry);
            cout << word << " has been added to the dictionary\n";

		}
		if (input == "remove")
		{
			string lineWithOutInput = line.substr(input.size()+1, line.size());
			string word = lineWithOutInput.substr(0, lineWithOutInput.find(' '));
			_dict.remove(word);
            cout << word << " has been deleted\n";
		}
		if (input == "define")
		{
			string lineWithOutInput = line.substr(input.size()+1, line.size());
			string word = lineWithOutInput.substr(0, lineWithOutInput.find(' '));

			Word *temp;
			temp = _dict.find(word);
			if (temp != nullptr)
			{
				cout << temp->myword << ":" << temp->definition << "\n";
				cout << "The word has been found\n";
			}
			else
			{
				cout << "The word has not been found\n";
			}
		}
		else if (input == "load") {
            string filename = line.substr(input.size() + 1, line.size());
            filename[11] = toupper(filename[11]);
            cout << filename << ": has been loaded \n";

            int quoteCounter = 0, location1 = 0, location2 = 0, location3 = 0, location4 = 0;
            ifstream infile(filename);
            if (infile.is_open()) {
                string stringType;

                while (getline(infile, stringType)) {
                    int quoteCounter = 0, location1 = 0, location2 = 0, location3 = 0, location4 = 0, startWord = 0, startDefin = 0, arrayIndex = 0;
                    int quotes[20] = {0};
                    string word = "";
                    string definit = "";
                    size_t found = stringType.find("word");
                    int stringSize = stringType.size();
                    if (found != string::npos) {
                        for (int i = 0; i < stringSize; i++) {
                            if (stringType[i] == '\"') {
                                quoteCounter++;
                                arrayIndex++;
                                quotes[arrayIndex] = i;
                                if (quoteCounter == 3) {
                                    location1 = i + 1; //start of word
                                    startWord = 0;
                                }
                                if (quoteCounter == 4) {
                                    location2 = startWord - 1; //end of wordj
                                }
                                if (quoteCounter == 7) {
                                    location3 = i + 1; //start of definition
                                    startDefin = 0;
                                }
                                if (quoteCounter == 8) {
                                    location4 = startDefin - 1; //end of definiton
                                }
                            }
                            startWord++;
                            startDefin++;
                        }
                        if (quoteCounter > 8) //if there are quotes in the definiton
                        {
                            location3 = quotes[7] + 1;
                            location4 = startDefin - 3;
                        }
                        word = stringType.substr(location1, location2);
                        definit = stringType.substr(location3, location4);
                        for (unsigned int i = 0; i < word.size(); i++) {
                            word[i] = tolower(word[i]);
                        }
                        Word entry;
                        entry.myword = word;
                        entry.definition = definit;
                        _dict.insert(word, entry);
                        //cout << word << " has been added to the dictionary\n";
                    }
                }

            }
            else
            {
                cout << "File was unable to open\n";
            }
            infile.close();
            infile.clear();
        }
		else if (input == "unload")
		{
            string filename2 = line.substr(input.size() + 1, line.size());
            filename2[11] = toupper(filename2[11]);
            cout << filename2 << ": has been unloaded \n";

            int quoteCounter = 0, location1 = 0, location2 = 0, location3 = 0, location4 = 0;

            ifstream infile2(filename2);

            if (infile2.is_open()) {
                string stringType2;

                while (getline(infile2, stringType2)) {
                    int quoteCounter = 0, location1 = 0, location2 = 0, location3 = 0, location4 = 0, startWord = 0, startDefin = 0, arrayIndex = 0;
                    int quotes[20] = {0};
                    string word = "";
                    string definit = "";
                    size_t found = stringType2.find("word");
                    int stringSize = stringType2.size();
                    if (found != string::npos) {
                        for (int i = 0; i < stringSize; i++) {
                            if (stringType2[i] == '\"') {
                                quoteCounter++;
                                arrayIndex++;
                                quotes[arrayIndex] = i;
                                if (quoteCounter == 3) {
                                    location1 = i + 1; //start of word
                                    startWord = 0;
                                }
                                if (quoteCounter == 4) {
                                    location2 = startWord - 1; //end of wordj
                                }
                                if (quoteCounter == 7) {
                                    location3 = i + 1; //start of definition
                                    startDefin = 0;
                                }
                                if (quoteCounter == 8) {
                                    location4 = startDefin - 1; //end of definiton
                                }
                            }
                            startWord++;
                            startDefin++;
                        }
                        if (quoteCounter > 8) //if there are quotes in the definiton
                        {
                            location3 = quotes[7] + 1;
                            location4 = startDefin - 3;
                        }
                        word = stringType2.substr(location1, location2);
                        definit = stringType2.substr(location3, location4);
                        for (unsigned int i = 0; i < word.size(); i++) {
                            word[i] = tolower(word[i]);
                        }
                        //cout << "TO DELETE: " << word;
                        _dict.remove(word);
                        //cout << word << " has been added to the dictionary\n";
                    }
                }

            }

            else
            {
                cout << "File was unable to open\n";
            }
            infile2.close();
            infile2.clear();
        }
        else if (input == "size")
        {
            cout << "Size of dictionary : " << _dict.size() << "\n";
        }
        else if (input == "clear")
        {
            _dict.clear();
            cout << "The dictionary has been cleared\n";
        }
        else if (input == "print")
        {
            int size;

            if (line.size() == 5)
            {
                size = _dict.size();
            }
            else
            {
                string lineWithOutInput = line.substr(input.size()+1, line.size());
                size = stoi(lineWithOutInput);

            }
            _dict.print(size);
        }
        else if (input == "random")
        {
            _dict.printRandom();
        }
        else if (input == "quit")
        {
            cout << "Thanks for visiting the dictinary";
        }
		cout << endl;
	}

public:
	Dictionary()	// Default constructor
	{ }

	/**
	*  Run the main dictionary user interface
	*/
	void run_ui() {
		// print out header
		cout << "+------------------------------------------+" << endl;
		cout << "|-- Welcome to the best dictionary evar! --|" << endl;
		cout << "+------------------------------------------+" << endl;

		string instr;
		cout << " Enter command (^D or EOF quits): ";
		// read in user input until eof
		while (getline(cin, instr)) {
			cout << endl << " --debug-- Entered command: " << instr << endl;
			parseline(instr);
			// call function based on line contents
			// print results

			cout << "Enter command: ";
		}
		cout << endl;
	}

};





#endif
