#include "match.h"
#include <SFML\System.hpp>
#include <SFML\Main.hpp>
#include <time.h>
#include "HighScores.h"


void match::playerTurn(bool doAtk, int keyPressed) {
	srand((unsigned int)time(NULL));
	unsigned int chance = rand() % 100 + 1;
	if (!startingMenu && keyPressed == 12 && howToMenu) { // how to menu displayed
		howToMenu = false;
	}
	if (startingMenu && keyPressed == 11) { // start menu displayed
		startingMenu = false;
	}
	
	if (!startingMenu) {
		if (deadScene && keyPressed == 10) {
			// resets all the stats for the Enemy and Hero objects after a game is finished. 
			player.addToMainStats(player.getMaxHP() * -1, player.getMaxMana() * -1, player.getAcc() * -1, player.getInt() * -1);
			player.addToMainStats(25, 10, 0, 0);
			enemy.addToMainStats(enemy.getMaxHP() * -1, enemy.getMaxMana() * -1, enemy.getAcc() * -1, enemy.getInt() * -1);
			enemy.addToMainStats(15, 10, 0, 0);
		
			isPlayerTurn = 1;
			deadScene = false;
			startingMenu = true;
			howToMenu = true;
			
			rounds = 0;

		}
		if (!deadScene && !menuScene) {
			// System waits for an input from the user, then will add to the correct stat that is chosen. 

			if (keyPressed == 6 && statMenu) {
				player.addToMainStats(5, 0, 0, 0);
				enemy.addToMainStats(2, 2, 2, 1);
				statMenu = false;
			}
			if (keyPressed == 7 && statMenu) {
				player.addToMainStats(0, 2, 0, 0);
				enemy.addToMainStats(2, 2, 2, 1);
				statMenu = false;
			}
			if (keyPressed == 8 && statMenu) {
				player.addToMainStats(0, 0, 8, 0);
				enemy.addToMainStats(2, 2, 2, 1);
				statMenu = false;
			}
			if (keyPressed == 9 && statMenu) {
				player.addToMainStats(0, 0, 0, 2);
				enemy.addToMainStats(2, 2, 2, 1);
				statMenu = false;
			}

			if (isPlayerTurn == 1 && !statMenu) {

				if (doAtk) {
					std::cout << "\n" << chance << std::endl;
					missedAtk = false;
					failedAtk = false;
					if (keyPressed == 0 && player.getMana() >= 0) { // air attack attempted
						failedAtk = false;
						std::cout << "player turn and attacked ";
						isPlayerTurn = 3;
						if (chance < 90 + player.getAcc()) {
							dmgDone = 3 + player.getInt();
							attack.AnimateAttack(false, "air1.png", 100, 100, 5, 10, 10, 'r');
						}
						else {
							missedAtk = true;
							attack.AnimateAttack(false, "empty.png", 100, 100, 7, 10, 10, 'r');
						}
						manaUsed = 0;
						player.changeStats(0, manaUsed);
						doAtk = false;

					}
					else if (keyPressed == 1 && player.getMana() >= 2) { // ice attack attempted
						failedAtk = false;
						std::cout << "player turn and attacked ";
						isPlayerTurn = 3;
						if (chance < 70 + player.getAcc()) {
							dmgDone = 5 + player.getInt();
							attack.AnimateAttack(false, "ice1.png", 100, 100, 8, 10, 10, 'r');
						}
						else {
							missedAtk = true;
							attack.AnimateAttack(false, "empty.png", 100, 100, 7, 10, 10, 'r');
						}
						manaUsed = 2;
						player.changeStats(0, manaUsed);
						doAtk = false;

					}
					else if (keyPressed == 2 && player.getMana() >= 4) { // fire attack attempted
						failedAtk = false;
						std::cout << "player turn and attacked ";
						isPlayerTurn = 3;
						if (chance < 60 + player.getAcc()) {
							dmgDone = 8 + player.getInt();
							attack.AnimateAttack(false, "fire1.png", 100, 100, 6, 10, 10, 'r');
						}
						else {
							missedAtk = true;
							attack.AnimateAttack(false, "empty.png", 100, 100, 7, 10, 10, 'r');
						}
						manaUsed = 4;
						player.changeStats(0, manaUsed);
						doAtk = false;

					}
					else if (keyPressed == 3 && player.getMana() >= 5) { // electric attack attempted
						failedAtk = false;
						std::cout << "player turn and attacked ";
						isPlayerTurn = 3;
						if (chance < 50 + player.getAcc()) {
							dmgDone = 13 + player.getInt();
							attack.AnimateAttack(false, "electric1.png", 100, 100, 9, 10, 10, 'r');
						}
						else {
							missedAtk = true;
							attack.AnimateAttack(false, "empty.png", 100, 100, 7, 10, 10, 'r');
						}
						manaUsed = 5;
						player.changeStats(0, manaUsed);
						doAtk = false;

					}
					else if (keyPressed == 4) { //HEALTH regen attempted
						failedAtk = false;
						std::cout << "player turn and attacked ";
						isPlayerTurn = 3;
						if (chance < 80 + player.getAcc() && player.getMana() > 0) {
							player.changeStats(-7 - player.getInt(), 1);
						}
						else if (chance < 70 + player.getAcc()) {
							player.changeStats(-5 - player.getInt(), 0);
						}
						else if (chance > 93)
						{
							player.changeStats((player.getMaxHP()) * -1, 1);
						}
						else {
							missedAtk = true;
							attack.AnimateAttack(false, "empty.png", 100, 100, 15, 10, 10, 'r');
						}
						attack.AnimateAttack(false, "empty.png", 100, 100, 7, 10, 10, 'r');
						doAtk = false;

					}
					else if (keyPressed == 5) { //MANA regen attempted
						failedAtk = false;
						std::cout << "player turn and attacked ";
						player.changeStats(0, -4);
						isPlayerTurn = 3;
						attack.AnimateAttack(false, "empty.png", 100, 100, 7, 10, 10, 'r');
						doAtk = false;
					}
					else {
						failedAtk = true;
					}
				}
			}
			bool temp = attack.moveRight();
			if (attack.getIsFinished() && isPlayerTurn == 3) {
				// enemy HP changed based on the success or failure of an attempted move
				std::cout << "\n" << dmgDone << std::endl;
				enemy.changeStats(dmgDone, 0);
				std::cout << "Player turn finished! ";
				isPlayerTurn = 0;
				dmgDone = 0;
				manaUsed = 0;
				failedAtk = false;
				missedAtk = false;

			}
		}
	}
}


void match::enemyTurn(bool doAtk) {

	srand((unsigned int)time(NULL));
	unsigned int chance = rand() % 100 + 1;
		if (isPlayerTurn == 0) {
				std::cout << "enemy turn started ";
				if (chance < 70 - enemy.getAcc() && enemy.getHP() > 0) { // normal attack for the enemy is used
					attack.AnimateAttack(true, "evil2.png", 100, 100, 6, 10, 10, 'r');
					if (enemy.getMana() >= 0)
						dmgDone = 3 + enemy.getIntel();
					else
						dmgDone = 1 + enemy.getIntel();
					enemy.changeStats(0, 2);
					isPlayerTurn = 2;
				}
				else if (chance < 80 + enemy.getAcc() && enemy.getHP() > 0) {	// super attack for the enemy is used	
					attack.AnimateAttack(true, "evil2.png", 100, 100, 3, 10, 10, 'r');
					attack.setColor(enemy.getColor());
					
					if (enemy.getMana() > 0)
						dmgDone = 10 + enemy.getIntel();
					else
						dmgDone = 6;
					enemy.changeStats(0, 2);
					isPlayerTurn = 2;
				}
				else if(enemy.getHP() > 0) // if the enemy still has HP left
				{
					// animate the correct attack
					missedAtk = true;
					isPlayerTurn = 2;
					attack.AnimateAttack(true, "empty.png", 100, 100, 6, 10, 10, 'r');
					
					if (enemy.getMana() >= 0)
						dmgDone = 0;
					else
						dmgDone = 0;
					enemy.changeStats(0, 2);
				}
				else { // Enemy color set based on round number
					if(rounds % 2 == 0)
						enemy.setColor(sf::Color::Red);
					else if (rounds % 3 == 0)
						enemy.setColor(sf::Color::White);
					if (rounds % 4 == 0)
						enemy.setColor(sf::Color::Green);
					else if (rounds % 5 == 0)
						enemy.setColor(sf::Color::Yellow);
					
				
					attack.AnimateAttack(false, "empty.png", 100, 100, 7, 10, 10, 'r');
					//std::cout << "\n\n\nACTIVATED" << attack.getIsFinished() << "\n\n\n";
					//attack.setIsFinished(true);
					isPlayerTurn = 2;
				}
		
			
		}
		bool temp = attack.moveLeft();
		if (player.getHP() < 1) {
			deadScene = true;
		}
		if ((attack.getIsFinished() && isPlayerTurn == 2) && enemy.getHP() > 0) { // color of attack is reset and damage is dealt to the player Hero
			attack.setColor(sf::Color::White);
			isPlayerTurn = 1;
			//std::cout << " switched Sides ";
			player.changeStats(dmgDone, 0);
			dmgDone = 0;
			missedAtk = false;
		}
		if ((enemy.getHP() < 1 && isPlayerTurn == 2)) { // attack color is reset and both the Hero and Enemy Stats are reset. 
			attack.setColor(sf::Color::White);
			isPlayerTurn = 1;
			rounds++;
			statMenu = true;
			std::cout << "CURRENT TOTAL POINTS: " << rounds << std::endl;
			std::cout << " switched Sides ";
			player.changeStats(dmgDone, 0);
			dmgDone = 0;
			enemy.changeStats(enemy.getMaxHP() * -1, enemy.getMaxMana() * -1);
			player.changeStats(player.getMaxHP() * -1, player.getMaxMana() * -1);
			missedAtk = false;
			startingMenu = false;
		}
		
	
}
