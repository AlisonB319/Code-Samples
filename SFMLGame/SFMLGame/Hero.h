#pragma once
#include <string>
#include "Character.h"

//struct to keep track of the hero stats
struct heroAttacks {
	std::string name;
	int dmg;
	int cost;
	char element;
	int accuracy;
};

class Hero : public Character {
public:
	//constructor
	Hero() {

	}
	//constructor
	Hero(std::string fileName, int pixelWidth, int pixelHeight) : Character(fileName,  pixelWidth,  pixelHeight) {
		this->HP = 25;
		this->MaxHP = 25;
		std::cout << "CONSTRUCTOR CALLED!";
		this->mana = 10;
		this->MaxMana = 10;
		this->accuracy = 0;
		this->intelligence = 0;
		this->scale(sf::Vector2f(3.5, 3.5));
		this->setPosition(55, 190);
		clothing = sf::Color::Red;
		//this->setColor(clothing);
		name = "Wizard of Akylo!";
		myAttacks[0] = { "Gust and Breeze", 3, 0, 'a', 30 };
		myAttacks[1] = { "Hail Throw", 5, 2, 'i', 20 };
		myAttacks[2] = { "Small Flame", 8, 4, 'f', 15 };
		myAttacks[3] = { "Spark", 13, 5, 'e' ,0 }; 
	}
	//setters
	void setName(std::string newName) {
		name = newName;
	}
	//getters
	int getHP() {
		return HP;
	}
	int getMaxHP() {
		return MaxHP;
	}
	int getMana() {
		return mana;
	}
	int getMaxMana() {
		return MaxMana;
	}
	std::string getName() {
		return name;
	}
	//virtual function redefined, will change the stats of the hero during the game
	virtual void changeStats(int subHP, int subMana) override {
		this->HP -= subHP;
		this->mana -= subMana;
		if (HP > MaxHP)
			HP = MaxHP;
		if (mana > MaxMana)
			mana = MaxMana;
		if (HP < 0)
			HP = 0;
		if (mana < 0)
			mana = 0;
	}
	//virtual function redefined, will changed the max amounts for hero after each rounds ends
	virtual void addToMainStats(int newMaxHP, int newMaxMana, int newAccuracy, int newIntelligence) override {
		std::cout << "HFifhasdhfiashdfi\n";
		std::cout << MaxHP << std::endl;
		this->MaxHP += newMaxHP;
		std::cout << MaxHP << std::endl;
		MaxMana += newMaxMana;
		accuracy += newAccuracy;
		intelligence += newIntelligence;
		HP = MaxHP;
		MaxHP = HP;
		mana = MaxMana;
	}

private:
	//variable list for the struct
	heroAttacks myAttacks[4];
	std::string name;
	sf::Color clothing;
};