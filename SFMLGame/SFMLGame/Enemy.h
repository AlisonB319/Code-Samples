#pragma once
#include "Character.h"

//struct to keep track of the enemy stats
struct EnemyAttacks {
	std::string name;
	int dmg;
	int cost;
	char element;
	int accuracy;
};

class Enemy : public Character {
public:
	//constructor
	Enemy() {

	}
	//constructor
	Enemy(std::string fileName, int pixelWidth, int pixelHeight, std::string enemyName) : Character(fileName, pixelWidth, pixelHeight) {
		this->HP = 15;
		this->MaxHP = 15;
		this->mana = 10;
		this->MaxMana = 10;
		this->accuracy = 0;
		this->intelligence = 0;
		this->scale(sf::Vector2f(3, 3));
		this->setPosition(850, -45);
		clothing = sf::Color::Blue;
		this->setColor(clothing);
		name = enemyName;
		enemyAttacks[0] = { "Gust and Breeze", 3, 0, 'a', 30 };
		enemyAttacks[1] = { "Hail Throw", 5, 2, 'i', 20 };
		enemyAttacks[2] = { "Small Flame", 8, 4, 'f', 15 };
		enemyAttacks[3] = { "Spark", 13, 5, 'e' ,0 };
	}
	//virtual function redefined, will change the stats of the enemy during the game
	virtual void changeStats(int subHP, int subMana) override {
		this->HP -= subHP;
		std::cout << "      THIS IS ENEMY HP: " << this->HP << "      ";
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
	//virtual function redefined, will changed the max amounts for enemies after each rounds ends
	virtual void addToMainStats(int newMaxHP, int newMaxMana, int newAccuracy, int newIntelligence) override {
		MaxHP += newMaxHP;
		MaxMana += newMaxMana;
		accuracy += newAccuracy;
		intelligence += newIntelligence;
		HP = MaxHP;
		mana = MaxMana;
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
	int getIntel() {
		return intelligence;
	}
	int getAcc() {
		return accuracy;
	}

private:
	//struct to kepe track of the enemy attacks
	EnemyAttacks enemyAttacks[4];
	std::string name;
	//will change the color of the enemy
	sf::Color clothing;
};