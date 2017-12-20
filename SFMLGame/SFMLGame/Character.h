#pragma once

#include <SFML\Graphics.hpp>
#include <string>

class Character : public sf::Sprite {
public:
	Character() {

	}
	Character(std::string textureImg, int pixelWidth, int pixelHeight) {
		texture.loadFromFile(textureImg, sf::IntRect(0, 0, pixelWidth, pixelHeight));
		this->setTexture(texture);
	}
	
	virtual void changeStats(int subHP, int subMana) = 0;
	virtual void addToMainStats(int newMaxHP, int newMaxMana, int newAccuracy, int newIntelligence) = 0;

	int getInt() {
		return intelligence;
	}
	int getAcc() {
		return accuracy;
	}
	
protected:
	std::string name;
	sf::Texture texture;
	int HP;
	int MaxHP;
	int mana;
	int MaxMana;
	int accuracy;
	int intelligence;
	int x;
	int y;
};
