/*******************************************************************************************
* Programmer: Niko, Alison, Kyle                                                           *
* Class: CptS 122, Summer  2017                                                            *
* Programming Assignment: 7                                                                *
* Date: July 26, 2017                                                                      *
* Description: This program is a wizard game!                                              *
*                                                                                          *
*******************************************************************************************/
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML\Network.hpp>
#include "Hero.h"
#include "Enemy.h"
#include "Attacks.h"
#include "match.h"
#include "HighScores.h"

int main()
{
	HighScores testMe;
	testMe.loadScores();


	sf::RenderWindow window(sf::VideoMode(1400, 800), "Battle of Akylo!");
	
	//Line 20 - 99 are all sprite creations with textures of image files assigned to each of them
	sf::Sprite background;
	sf::Texture bg;
	bg.loadFromFile("background.png", sf::IntRect(0, 0, 1400, 800));

	sf::Sprite startMenu;
	sf::Texture menuIMG;
	menuIMG.loadFromFile("startMenu.png", sf::IntRect(0, 0, 1400, 800));
	startMenu.setTexture(menuIMG);
	startMenu.setPosition(0, 0);

	sf::Sprite howtoplay;
	sf::Texture howtoIMG;
	howtoIMG.loadFromFile("HowToPlay.png", sf::IntRect(0, 0, 1400, 800));
	howtoplay.setTexture(howtoIMG);
	howtoplay.setPosition(0, 0);

	sf::Sprite airAtk;
	sf::Texture airImg;
	airImg.loadFromFile("Air.png", sf::IntRect(0, 0, 223, 100));
	airAtk.setTexture(airImg);
	airAtk.setPosition(460, 700);

	sf::Sprite IceAtk;
	sf::Texture IceImg;
	IceImg.loadFromFile("NewIce.png", sf::IntRect(0, 0, 223, 100));
	IceAtk.setTexture(IceImg);
	IceAtk.setPosition(683, 700);

	sf::Sprite FireAtk;
	sf::Texture FireImg;
	FireImg.loadFromFile("fire.png", sf::IntRect(0, 0, 223, 100));
	FireAtk.setTexture(FireImg);
	FireAtk.setPosition(906, 700);

	sf::Sprite ElcAtk;
	sf::Texture ElcImg;
	ElcImg.loadFromFile("electric.png", sf::IntRect(0, 0, 223, 100));
	ElcAtk.setTexture(ElcImg);
	ElcAtk.setPosition(1129, 700);

	sf::Sprite HealthAtk;
	sf::Texture HealthImg;
	HealthImg.loadFromFile("NewHealth.png", sf::IntRect(0, 0, 223, 100));
	HealthAtk.setTexture(HealthImg);
	HealthAtk.setPosition(243, 700);


	sf::Sprite manaAtk;
	sf::Texture manaImg;
	manaImg.loadFromFile("mana.png", sf::IntRect(0, 0, 223, 100));
	manaAtk.setTexture(manaImg);
	manaAtk.setPosition(30, 700);

	sf::Sprite statMenu;
	sf::Texture statImg;
	statImg.loadFromFile("StatMenu.png", sf::IntRect(0, 0, 1400, 800));
	statMenu.setTexture(statImg);
	statMenu.setPosition(0, 0);

	sf::Sprite statHero;
	sf::Texture heroImg;
	heroImg.loadFromFile("player.png", sf::IntRect(0, 0, 100, 100));
	statHero.setTexture(heroImg);
	statHero.scale(-4.5f, 4.5f);
	statHero.setPosition(1100, 100);

	sf::Sprite deadHero;
	deadHero.setTexture(heroImg);
	deadHero.scale(4.5f, 4.5f);
	deadHero.setRotation(-90);
	deadHero.setPosition(300, 800);

	sf::Sprite deathScreen;
	sf::Texture deathIMG;
	deathIMG.loadFromFile("deathScreen.png", sf::IntRect(0, 0, 1400, 800));
	deathScreen.setTexture(deathIMG);
	deathScreen.setPosition(0, 0);

	//setting up background
	background.setTexture(bg);
	background.setPosition(0, 0);
	match myGame; //the main wrapper for the game
	bool playerAtk = false; //used for passing values into the myGame object
	bool enemyAtk = false;//used for passing values into the myGame object

	//following is the setup for all text used in the game
	sf::Font gameFont;
	gameFont.loadFromFile("SourceSansPro-Light.otf");
	sf::Text title;
	title.setFont(gameFont);
	title.setCharacterSize(65);
	title.setString("Battle for Akylo!");
	title.setPosition(sf::Vector2f(450, 0));


	sf::Text atkTitle;
	atkTitle.setFont(gameFont);
	atkTitle.setCharacterSize(65);
	atkTitle.setString("");
	atkTitle.setPosition(sf::Vector2f(450, 150));

	sf::Text heroStatus;
	heroStatus.setFont(gameFont);
	heroStatus.setCharacterSize(65);
	heroStatus.setString("fahsdfha");
	heroStatus.setColor(sf::Color::Magenta);
	heroStatus.setPosition(sf::Vector2f(100, 500)); 

	sf::Text enemyStatus;
	enemyStatus.setFont(gameFont);
	enemyStatus.setCharacterSize(65);
	enemyStatus.setString("fahsdfha");
	enemyStatus.setColor(sf::Color::Magenta);
	enemyStatus.setPosition(sf::Vector2f(1000, 500));

	sf::Text winText;
	winText.setFont(gameFont);
	winText.setCharacterSize(45);
	winText.setString("You Defeated the Wizard!");
	winText.setColor(sf::Color::White);
	winText.setPosition(sf::Vector2f(800, 200));

	sf::Text deadText;
	deadText.setFont(gameFont);
	deadText.setCharacterSize(150);	
	deadText.setColor(sf::Color::White);
	deadText.setPosition(sf::Vector2f(280, 180));

	sf::Text pressSpace;
	pressSpace.setFont(gameFont);
	pressSpace.setCharacterSize(85);
	pressSpace.setColor(sf::Color::White);
	pressSpace.setPosition(sf::Vector2f(270, 660));

	sf::Text HighScore;
	HighScore.setFont(gameFont);
	HighScore.setCharacterSize(45);
	HighScore.setColor(sf::Color::Black);
	HighScore.setPosition(sf::Vector2f(200, 18));

	sf::Text HighScore2;
	HighScore2.setFont(gameFont);
	HighScore2.setCharacterSize(45);
	HighScore2.setColor(sf::Color::Black);
	HighScore2.setPosition(sf::Vector2f(200, 65));

	sf::Text HighScore3;
	HighScore3.setFont(gameFont);
	HighScore3.setCharacterSize(45);
	HighScore3.setColor(sf::Color::Black);
	HighScore3.setPosition(sf::Vector2f(200, 113));

	sf::Text HeroName;
	HeroName.setFont(gameFont);
	HeroName.setCharacterSize(45);
	HeroName.setColor(sf::Color::Black);
	HeroName.setPosition(sf::Vector2f(500, 300));

	sf::Text HeroPrompt;
	HeroPrompt.setFont(gameFont);
	HeroPrompt.setCharacterSize(45);
	HeroPrompt.setColor(sf::Color::Black);
	HeroPrompt.setPosition(sf::Vector2f(275, 220));

	int abilityUsed = 0; //used to pass into myGame.playerturn() and .enemyturn()
	int rot = 0; //used to set rotation of wizard at stat menu and is always incremented by 1
	bool LoadedScore = false; //bool for whether or not most recent score is downloaded from server
	bool stopName = false; //bool to stop getting user text for name

	std::string heroName = " "; //hero name
	int i = 0; 
	while (window.isOpen()) //the loop for updating game frame by frame
	{
		sf::Event event;	
		//window.draw(s);
		while (window.pollEvent(event)) //if there is an actual event, this loop runs
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
			if (event.type == sf::Event::KeyPressed)
			{
				
				//used for air attack
				if (event.key.code == sf::Keyboard::Q && !myGame.getStatMenu()) {
					playerAtk = true;
					abilityUsed = 0;
					if(!myGame.getAtk().getIsFinished()) {
						atkTitle.setString("Air Attack!");
					}
				}
				//used for ice attack
				if (event.key.code == sf::Keyboard::W && !myGame.getStatMenu()) {
					playerAtk = true;
					abilityUsed = 1;
					if (!myGame.getAtk().getIsFinished()) {
						atkTitle.setString("Ice Attack!");
					}
				}
				//used for fire attack
				if (event.key.code == sf::Keyboard::E && !myGame.getStatMenu()) {
					playerAtk = true;
					abilityUsed = 2;
					std::cout << myGame.getAtk().getIsFinished();
					if (!myGame.getAtk().getIsFinished()) {
						atkTitle.setString("Fire Attack!");
					}
				}
				//used for electric attack
				if (event.key.code == sf::Keyboard::R && !myGame.getStatMenu()) {
					playerAtk = true;
					abilityUsed = 3;
					if (!myGame.getAtk().getIsFinished()) {
						atkTitle.setString("Electric Attack!");
					}
				}
				//used to self heal
				if (event.key.code == sf::Keyboard::A && !myGame.getStatMenu()) {
					playerAtk = true;
					abilityUsed = 4;
					if (!myGame.getAtk().getIsFinished()) {
						atkTitle.setString("Attempted to Heal!");
					}
				}
				//used to regen mana
				if (event.key.code == sf::Keyboard::S && !myGame.getStatMenu()) {
					playerAtk = true;
					abilityUsed = 5;
					if (!myGame.getAtk().getIsFinished()) {
						atkTitle.setString("Mana Regenerate!");
					}
				}
				//used to increase health at stat menu
				if (event.key.code == sf::Keyboard::Num1 && myGame.getStatMenu()) {
					abilityUsed = 6;
				}
				//used to increase Mana at stat menu
				if (event.key.code == sf::Keyboard::Num2 && myGame.getStatMenu()) {
					abilityUsed = 7;
				}
				//used to increase Accuracy at stat menu
				if (event.key.code == sf::Keyboard::Num3 && myGame.getStatMenu()) {
					abilityUsed = 8;
				}
				//used to increase Intelligence at stat menu
				if (event.key.code == sf::Keyboard::Num4 && myGame.getStatMenu()) {
					abilityUsed = 9;
				}
				//return from death menu to starting menu
				if (event.key.code == sf::Keyboard::Space && myGame.getIsDeathMenu()) {
					playerAtk = true;
					
					abilityUsed = 10;

				}
				//move past start menu and end name editing
				if (event.key.code == sf::Keyboard::Return && myGame.getStartMenu()) {				
					playerAtk = true;
					abilityUsed = 11;
					stopName = true;
				}
				//move past how to menu on enter key pressed
				if (event.key.code == sf::Keyboard::Return && myGame.getHowToMenu() && !myGame.getStartMenu()) {
					playerAtk = true;
					abilityUsed = 12;
				}			
			}	
			//get hero name
			if (event.type == sf::Event::TextEntered && myGame.getStartMenu() && !stopName) {
				if (event.key.code != sf::Keyboard::BackSpace) {
					std::cout << " Key Hit! ";
					heroName += (char)event.text.unicode;
					HeroName.setString(heroName);
				}
			}		
		}

		std::string heroStats; //holds the stats for hero
		std::string enemyStats; //holds the stats for enemy
		enemyStats = "HP: " + std::to_string(myGame.getEnemy().getHP()) + '/' + std::to_string(myGame.getEnemy().getMaxHP()) + '\n' + "Mana: " + std::to_string(myGame.getEnemy().getMana()) + '/' + std::to_string(myGame.getEnemy().getMaxMana());
		heroStats = "HP: " + std::to_string(myGame.getHero().getHP()) +'/' + std::to_string(myGame.getHero().getMaxHP()) + '\n' + "Mana: " + std::to_string(myGame.getHero().getMana()) + '/' + std::to_string(myGame.getHero().getMaxMana());
		heroStatus.setString(heroStats); //sets strings
		enemyStatus.setString(enemyStats);

		if (myGame.getFail() && myGame.getHero().getMana() < 10) //Prompt for out of mana
			atkTitle.setString("Out of Mana! Pick new move");
		if (myGame.getRealFail()) {                             //prompt for Hero missed
			atkTitle.setString("Missed!");
		}
		if (myGame.getRealFail() && myGame.getIsPlayerTurn() == 2) { //prompt for enemy missed
			atkTitle.setString("Enemy Missed!");
		}


		if (myGame.getAtk().getIsFinished()) { //resets the string so its not sitting on screen
			atkTitle.setString("");
		}
		myGame.enemyTurn(enemyAtk); //run enemy turn based off of if it is their turn to attack
		myGame.playerTurn(playerAtk, abilityUsed); //run player turn based off if it is their turn to attack and what keypress was used
		playerAtk = false; //ends the player attack
		enemyAtk = false; //ends enemy attack

		statHero.setRotation(rot++); //Rotates hero while at stat menu
		if (rot % 7 == 0) { //Sparatically changes colors
			winText.setColor(sf::Color::Blue);
		}
		else if (rot % 13 == 0) {
			winText.setColor(sf::Color::Red);
		}
		else if (rot % 19 == 0) {
			winText.setColor(sf::Color::Green);
		}

		//All the winodw draw statements
		window.clear();
		window.draw(background);
		window.draw(myGame.getHero());
		window.draw(myGame.getEnemy());
		window.draw(myGame.getAtk());
		window.draw(title);
		window.draw(airAtk);
		window.draw(IceAtk);
		window.draw(FireAtk);
		window.draw(ElcAtk);
		window.draw(HealthAtk);
		window.draw(manaAtk);
		window.draw(atkTitle);
		window.draw(heroStatus);
		window.draw(enemyStatus);
		if (myGame.getStatMenu()) {
			window.draw(statMenu);
			window.draw(statHero);
			window.draw(winText);			
		}
		if (myGame.getIsDeathMenu()) { //if at death menu then handle score loading and saving and check if new scores should be uploaded
			window.draw(deathScreen);
			window.draw(deadHero);
			deadText.setString("Your Score is " + std::to_string(myGame.getRounds()));
			pressSpace.setString("Press Space Bar to restart");
			window.draw(deadText);
			window.draw(pressSpace);
			if (!LoadedScore) {                //tests the hero's score for the game vs the top 3 saved scores
				if (heroName.length() < 2)
					heroName = "Merlin";       //default name is merlin if nothing is saved at the beginning for hero name
				if (myGame.getRounds() > testMe.getScoreAt(0)) {
					testMe.setScoreAt(2, testMe.getScoreAt(1));
					testMe.setNameAt(2, testMe.getNameAt(1));
					testMe.setScoreAt(1, testMe.getScoreAt(0));
					testMe.setNameAt(1, testMe.getNameAt(0));
					testMe.setNameAt(0, heroName);
					testMe.setScoreAt(0, myGame.getRounds());
					
				}

				else if (myGame.getRounds() > testMe.getScoreAt(1)) {
					testMe.setScoreAt(2, testMe.getScoreAt(1));
					testMe.setNameAt(2, testMe.getNameAt(1));
					testMe.setNameAt(1, heroName);
					testMe.setScoreAt(1, myGame.getRounds());
				}

				else if (myGame.getRounds() > testMe.getScoreAt(2)) {
					testMe.setNameAt(2, heroName);
					testMe.setScoreAt(2, myGame.getRounds());
				}
				testMe.saveScores();
				heroName = "";
				LoadedScore = true;
			}
			HeroName.setString(heroName);
			stopName = false;
		}
		//draws how to play
		if (myGame.getHowToMenu()) {
			window.draw(howtoplay);
		}
		//draws starts menu
		if (myGame.getStartMenu()) {	
			LoadedScore = false;
			window.draw(startMenu);
			HighScore.setString(testMe.getNameAt(0) + ": " + std::to_string(testMe.getScoreAt(0)));
			window.draw(HighScore);
			HighScore2.setString(testMe.getNameAt(1) + ": " + std::to_string(testMe.getScoreAt(1)));
			window.draw(HighScore2);
			HighScore3.setString(testMe.getNameAt(2) + ": " + std::to_string(testMe.getScoreAt(2)));
			window.draw(HighScore3);
			window.draw(HeroName);
			HeroPrompt.setString("Please Enter Hero Name: (Default is \"Merlin\"))");
			window.draw(HeroPrompt);
		}
		window.display();


	}

	return 0;
}