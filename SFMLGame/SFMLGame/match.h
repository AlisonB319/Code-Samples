#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Enemy.h"
#include "Attacks.h"

class match {
public:
	//constructor 
	match() {		
		rounds = 0;
		isPlayerTurn = 1;
	}
	//constructor
	match(std::string heroName) {
		Hero myHero("player.png", 100, 100);
		player = myHero;
		player.setName(heroName);
		rounds = 0;
	}
	//function delcaration for everything that will happen during the player's turn
	void playerTurn(bool doAtk, int keyPressed);
	//function delcaration for everything that will happen during the enemy's turn
	void enemyTurn(bool doAtk);

	//getters
	int getRounds() {
		return rounds;
	}

	bool getIsDeathMenu() {
		return deadScene;
	}

	Hero getHero() {
		return player;
	}
	Enemy getEnemy() {
		return enemy;
	}
	Attacks getAtk() {
		return attack;
	}

	bool getFail() {
		return failedAtk;
	}
	bool getRealFail() {
		return missedAtk;
	}

	bool getStatMenu() {
		return statMenu;
	}
	void setStatMenu(bool newTruth) {
		statMenu = newTruth;
	}

	int getIsPlayerTurn() {
		return isPlayerTurn;
	}
	void runTimed(int newTime) {
		timed += newTime;
	}

	bool getStartMenu() {
		return startingMenu;
	}

	bool getHowToMenu() {
		return howToMenu;
	}

private:
	Hero player = Hero("player.png", 100, 100); //player image
	Enemy enemy = Enemy("enemy.png", 200, 200, "badguy"); //enemy inage
	Attacks attack; //attack variable decleration 
	int isPlayerTurn; //is it the players turn
	int rounds = 0; //variable for completed rounds
	int dmgDone = 0;
	int manaUsed = 0;
	int timed = 0;

	bool startingMenu = true; //will the starting menu be on the screen

	bool howToMenu = true; //will the how to menu be on the scree

	bool statMenu = false; //will the stat menu be on the scree

	bool failedAtk = false; //are you out of mana therefore the attack fails

	bool missedAtk = false; //did the attack miss

	bool deadScene = false; //will the dead screen be on the scree

	bool menuScene = false; //will the menu be on the scree

};