#pragma once

#include <SFML\Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

class HighScores {
public:
	HighScores()  {
		http.setHost("appdevclub.000webhostapp.com/");
	};

	void loadScores() {
		sf::Http::Request request;
		request.setUri("/showScores.php");
		request.setMethod(sf::Http::Request::Post);
		sf::Http::Response response = http.sendRequest(request);
		std::string temp = response.getBody();
		std::string tempNum = "";
		std::istringstream sep(temp);
		if (temp.length() > 5) {
			for (int i = 0; i < 3; i++) {
				std::getline(sep, tempNum, ',');
				scoreNames[i] = tempNum;
				std::getline(sep, tempNum, ',');
				highScore[i] = std::stoi(tempNum);
			}
			for (int i = 0; i < 3; i++) {
				std::cout << scoreNames[i] << std::endl;
				std::cout << highScore[i] << std::endl;
			}
		}
	}

	void saveScores() {
		sf::Http::Request request;
		request.setUri("/highscores.php");
		request.setMethod(sf::Http::Request::Post);
		std::string temp;
		for (int i = 0; i < 3; i++) {
			temp += scoreNames[i] + "," + std::to_string(highScore[i]) + ",";
		}
		request.setBody("score=" + temp);
		sf::Http::Response response = http.sendRequest(request);
		std::cout << response.getBody() << std::endl;
	}

	int getScoreAt(int n) {
		return highScore[n];
	}
	void setScoreAt(int n, int newScore) {
		highScore[n] = newScore;
	}
	std::string getNameAt(int n) {
		return scoreNames[n];
	}
	void setNameAt(int n, std::string newName) {
		scoreNames[n] = newName;
	}
	
	int isScoreTop(int score) {
		for (int i = 0; i < 3; i++) {
			if (score > highScore[i])
				return i;
		}
		return -1;
	}

private:
	sf::Http http;
	int highScore[3];
	std::string scoreNames[3];

};
