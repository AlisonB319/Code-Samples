#include "Attacks.h"
#include <iostream>


// getter functions for the main data members for the attacks
int Attacks::getDamage() {
	return dmg;
}
int Attacks::getManacost() {
	return manacost;
}
bool Attacks::getIsEnemy() {
	return isEnemy;
}

// setters for the data members for the attack class
void Attacks::setDamage(int newDmg) {
	dmg = newDmg;
}
void Attacks::setManacost(int newCost) {
	manacost = newCost;
}
void Attacks::setIsEnemy(bool t) {
	isEnemy = t;
}


// this function will load an image for an attack, set all the data members, and the animation for a single attack will be set. 
void Attacks::AnimateAttack(bool fromEnemy, std::string textureName, int pixelWidth, int pixelHeight,float newSpeed, int newDmg, int newManacost, char element) {

	// texture for attack is loaded
	texture.loadFromFile(textureName, sf::IntRect(0, 0, pixelWidth, pixelHeight));	
	this->setTexture(texture);
	this->setPosition(100, 100);
	
	// data members are set
	moveSpeed = newSpeed;
	dmg = newDmg;
	manacost = newManacost;
	elementType = element;
	isEnemy = fromEnemy;
	if (isEnemy) { //from enemy
		this->setPosition(1050, 275);
		std::cout << "atk set";
		moving = true;
		isFinished = false;
	}
	else { //hero
		this->setPosition(325, 290);
		moving = true;
		isFinished = false;
	}
}

// disappear function sets the image for an attack far of screen for storage until the object is used in the main function. 
void Attacks::disappear() {
	this->setPosition(-1000, -1000);
}

// This function sets the animation direction to move left for the Enemy.
bool Attacks::moveLeft() {
	sf::Vector2f curPos;
	curPos = this->getPosition();
	//std::cout << curPos.x << ", " << curPos.y;
	isFinished = false;
	if (isEnemy && moving && curPos.x > 300) {
		//std::cout << "moveLeft activated";
		this->setPosition(curPos.x - moveSpeed, curPos.y);
		//this->setScale(-1.0f, 1.0f);
		isFinished = false;
		return true;
	}
	
	if (curPos.x <= 300 && isEnemy && moving) {
		moving = false;
		isFinished = true;
		std::cout << "    ENEMY ATK FINISHED    ";
		disappear();
		return false;
	}
	return false;
}

// This function sets the animation direction to move Right for the Hero.
bool Attacks::moveRight() {
	//isFinished = false;
	sf::Vector2f curPos;
	curPos = this->getPosition();
	isFinished = false;
	if (!isEnemy && moving && curPos.x <1030) {
		//std::cout << "moveRight activated";
		this->setPosition(curPos.x + moveSpeed, curPos.y);
		this->setScale(1.0f, 1.0f);
		isFinished = false;
		//std::cout << "Still moving";
		return true;
	}
	if (curPos.x >= 1030 && !isEnemy && moving) {
		moving = false;
		isFinished = true;
		disappear();
		std::cout << "Finished";
		std::cout << isFinished;
		return false;
	}
	return false;
}