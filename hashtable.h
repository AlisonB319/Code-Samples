/**
*  Basic hash table implementation
*   Aaron S. Crandall - 2017 <acrandal@gmail.com>
*
*/

//I wrote this code
#ifndef __HASH_H
#define __HASH_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>

using namespace std;
/*
private:
void rehash();
int hash_function(KEYTYPE key);
public:i
bool insert(KEYTYPE key, VALTYPE val);
bool contains(KEYTYPE key);
int remove(KEYTYPE key);
VALTYPE & find(KEYTYPE key);
int size();            // Elements currently in table
bool empty();          // Is the hash empty?
float load_factor();   // Return current load factor
void clear();          // Empty out the table
int bucket_count();    // Total number of buckets in table
*/

template <typename KEYTYPE, typename VALTYPE>
class Hashtable
{
private:
	int maxSize;
	vector<list<VALTYPE>> hashT;

	/**
	*  Rehash the table into a larger table when the load factor is too large
	*/
	void rehash() {
		int newTsize;
		newTsize = maxSize * 2;
		bool found = false;
		while (!found)
		{
			newTsize++;
			for (int i = 2; i <= newTsize / 2; i++)
			{
				if (newTsize % i == 0)
					found = false;
			}
			found = true;
		}
		hashT.resize(newTsize);
		maxSize = newTsize;
	}

	/**
	*  Function that takes the key (a string or int) and returns the hash key
	*   This function needs to be implemented for several types it could be used with!
	*/
	int hash_function(int key) {
		//cout << " Hashing with int type keys." << endl;
		key = key % maxSize;
		return key;
	}

	int hash_function(string key) {
		//cout << " Hashing with string type keys." << endl;
		int seed = 101;
		unsigned long hash = 0;

		for (int i = 0; i < key.length(); i++)
		{
			hash = (hash * seed) + key[i];
			int temp = hash;
		}

		return hash % maxSize;
	}


public:
	/**
	*  Basic constructor
	*/
	Hashtable(int startingSize = 101)
	{
		//hashT is the structure 
		maxSize = startingSize;
		hashT.resize(startingSize);
	}

	/**
	*  Add an element to the hash table
	*/
	bool insert(KEYTYPE key, VALTYPE val) {
		int temp = 0;
		float load = 0;
		int sizet = 0;

		temp = hash_function(key);
		load = load_factor();
		sizet = size();
		if (load >= 1)
		{
			rehash();
		}
		hashT[temp].push_back(val);
		return false;
	}

	/**
	*  Return whether a given key is present in the hash table
	*/
	bool contains(KEYTYPE key) {
		int temp = 0;
		temp = hash_function(key);

		if (hashT[temp].size() != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	/**
	*  Completely remove key from hash table
	*   Returns number of elements removed
	*/
	int remove(KEYTYPE key)
    {
		// Doesn't actually remove anything yet
		int temp = hash_function(key);
		int numRemoved = 0;
        string iterS;
        string skey = key;
        Word *words = nullptr;

        typename list<VALTYPE>::iterator it = hashT[temp].begin();
        for (; it != hashT[temp].end(); it++)
        {
            words = &*it;
            iterS = words->myword;
            for (unsigned int i = 0; i < iterS.size(); i++)
            {
                iterS[i] = tolower(iterS[i]);
            }
            for (unsigned int i = 0; i < skey.size(); i++)
            {
                skey[i] = tolower(skey[i]);
            }
            if (iterS == skey)
            {
                //cout << "deleted: " << skey << endl;
                hashT[temp].erase(it);
                numRemoved++;
                break;
            }

        }

        return numRemoved;

    }



	/**
	*  Searches the hash and returns a pointer
	*   Pointer to Word if found, or nullptr if nothing matches
	*/
	VALTYPE *find(KEYTYPE key) {
		int temp = hash_function(key);
		Word *words = nullptr, *tempW = nullptr;
		string testS;
        typename list<VALTYPE>::iterator it = hashT[temp].begin();

		if (hashT[temp].size() != 0)
		{
			for (; it != hashT[temp].end(); ++it)
			{
				tempW = &*it;
				testS = tempW->myword;
				if (testS == key)
				{
					words = &*it;
					return words;
				}
			}
		}
		return nullptr;
	}

	/**
	*  Return current number of elements in hash table
	*/
	int size() {
		int count = 0;
		
		for (int i = 0; i < maxSize; i++)
		{
            count += hashT[i].size();
		}
		return count;
	}

	/**
	*  Return true if hash table is empty, false otherwise
	*/
	bool empty() {
		int sizeN = size();
		if (sizeN == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	*  Calculates the current load factor for the hash
	*/
	float load_factor() {
		//return _hash.load_factor();
		float n = size();
		float m = bucket_count();
		float fac = n / m;
		return fac; 
	}

	/**
	*  Returns current number of buckets (elements in vector)
	*/
	int bucket_count() {
		return maxSize;
	}

	/**
	*  Deletes all elements in the hash
	*/
	void clear() {
		for (int i = 0; i < maxSize; i++)
		{
			while (hashT[i].size() != 0)
			{
				hashT[i].pop_back();
			}
		}
	}

    void print(int size)
    {
        string key;
        string testS;
        Word *tempW;
        int maxNums = 0;

        for (int temp = 0; temp < maxSize; temp++)
        {
            typename list<VALTYPE>::iterator it = hashT[temp].begin();
            if (hashT[temp].size() != 0)
            {
                for (; it != hashT[temp].end(); ++it)
                {
                    if (maxNums != size )
                    {
                        tempW = &*it;
                        testS = tempW->myword;
                        cout << testS << " ";
                        maxNums++;
                    }
                }
            }
        }
    }
    void printRandom()
    {
        bool notprinted = true;
        Word *words = nullptr, *tempW = nullptr;
        string testS;

        while (notprinted)
        {
            int temp = rand() % maxSize;
            //cout << "temp: " << temp << endl;
            typename list<VALTYPE>::iterator it = hashT[temp].begin();
            if (hashT[temp].size() != 0)
            {
                tempW = &*it;
                testS = tempW->myword;
                cout << "Random Word: " << testS << endl;
                notprinted = false;
            }
        }
    }

};


#endif
