#pragma once

#include <SFML\Graphics.hpp>

//mneed to use virtual destructors for polymorphic behaviors

class Attacks :  public sf::Sprite {
public:
	//constructor 
	Attacks() {
		moving = false;
		this->setPosition(-1000, -1000);
	}
	//constructor
	Attacks(std::string fileName, int pixelWidth, int pixelHeight) {
		texture.loadFromFile(fileName, sf::IntRect(0, 0, pixelWidth, pixelHeight));
		this->setTexture(texture);
		moveSpeed = 20.0f;
		dmg = 3;
		manacost = 1;
		elementType = 'a';
		moving = false;
		this->setPosition(-1000, -1000);
		
	}
	//getters
	int getDamage();
	int getManacost();
	bool getIsEnemy();
	float getX() {
		return x;
	}
	void setX(){
		x = this->getPosition().x;
	}
	float getY() {
		return y;
	}
	void setY() {
		y = this->getPosition().y;
	}

	sf::Vector2f getPos() {
		return this->getPosition();
	}

	bool getIsFinished() {
		return isFinished;
	}
	void setIsFinished(bool newVal) {
		isFinished = newVal;
	}
	//setters
	void setDamage(int newDmg);
	void setManacost(int newCost);
	void setIsEnemy(bool t);
	//will animate the attack
	void AnimateAttack(bool fromEnemy, std::string textureName, int pixelWidth, int pixelHeight, float newSpeed, int newDmg, int newManacost, char element);
	//will determine the direction of the attack
	bool moveLeft();
	bool moveRight();
	//will put the attack off screen
	void disappear();


private:
	bool isFinished = false; //is the attack finished
	float x; //position x for the attack animation
	float y; //position y for the attack animation
	bool isEnemy; //is it the enemy's attack
	bool moving; //is the attack still moving
	sf::Texture texture;
	//stats for the attack
	float moveSpeed;
	int dmg;
	int manacost;
	char elementType;
};
