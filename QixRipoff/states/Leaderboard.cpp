#include "../toolbox/toolbox.hpp"
#include "Leaderboard.hpp"
#include "../Core.hpp"
#include "../resources/Textures.hpp"

namespace states {
	Leaderboard::Leaderboard(Core* _core):score(_core->getScores()) {
		this->core = _core;

		for (int i = 0; i < 3; i++) this->selections[i] = 0;
		this->selectProgress = -1;
	}

	void Leaderboard::init() {
		for (int i = 0; i < 3; i++) this->selections[i] = 0;
		this->selectProgress = -1;
		if (Score::enterLeaderboard != -1) {
			this->selectProgress = 0;
		}

		Leaderboard::txtFont.loadFromFile("../assets/fonts/qix-small.ttf");
		Leaderboard::txtDisplay.setFont(Leaderboard::txtFont);
		Leaderboard::txtDisplay.setCharacterSize(12);

		Texture::preload("../assets/Textures/bgMenu.png", "bgMenu");
		Texture::treatPinkPixels("bgMenu");
	}

	void Leaderboard::update() {
		if (this->selectProgress == -1) {
			if (this->core->getKeyboard().pressed("OK")) {
				this->core->requestStateChange(MENU);
			}
		}
		else {
			if (this->core->getKeyboard().pressed("OK")) {
				if (this->selectProgress == 2) {
					this->selectProgress = -1;
					Score::highscores[Score::enterLeaderboard].name = this->buildNameString();
				}
				else this->selectProgress++;
			}
			if (this->core->getKeyboard().pressed("Kaboom") && this->selectProgress > 0) {
				this->selectProgress--;
			}

			if (this->core->getKeyboard().pressed("Up")) {
				this->selections[this->selectProgress] = ++this->selections[this->selectProgress] % 26;
			}
			if (this->core->getKeyboard().pressed("Down")) {
				this->selections[this->selectProgress] = (--this->selections[this->selectProgress] + 26) % 26;
			}
		}
	}

	void Leaderboard::render() {
		std::string strRender;

		sprDisplay.setScale(1.f, 1.f);
		sprDisplay.setPosition(0, 0);
		sprDisplay.setTexture(Texture::getTexture("bgMenu"));
		this->core->getWindow().draw(sprDisplay);

		if (this->selectProgress == -1) {
			for (int i = 0; i < 5; i++) {
				strRender = "";
				strRender += std::to_string(Score::highscores[i].score);
				strRender.insert(strRender.begin(), 12 - strRender.size(), ' ');
				txtDisplay.setString(Score::highscores[i].name + strRender);

				Leaderboard::txtDisplay.setFillColor(sf::Color::White);
				Leaderboard::txtDisplay.setPosition(128.f, 100.f + i * 16.f);
				Leaderboard::txtDisplay.setOrigin(sf::Vector2f(Leaderboard::txtDisplay.getGlobalBounds().width, Leaderboard::txtDisplay.getGlobalBounds().height) * .5f);
				this->core->getWindow().draw(Leaderboard::txtDisplay);
			}
		}
		else {
			for (int i = 0; i < 5; i++) {
				if (Score::enterLeaderboard == i) {
					strRender = "";
					strRender += std::to_string(Score::highscores[i].score);
					strRender.insert(strRender.begin(), 12 - strRender.size(), ' ');
					txtDisplay.setString(this->buildNameString() + strRender);
					Leaderboard::txtDisplay.setFillColor(sf::Color::Green);
				}

				else {
					strRender = "";
					strRender += std::to_string(Score::highscores[i].score);
					strRender.insert(strRender.begin(), 12 - strRender.size(), ' ');
					txtDisplay.setString(Score::highscores[i].name + strRender);
					Leaderboard::txtDisplay.setFillColor(sf::Color::White);
				}

				Leaderboard::txtDisplay.setPosition(128.f, 100.f + i * 16.f);
				Leaderboard::txtDisplay.setOrigin(sf::Vector2f(Leaderboard::txtDisplay.getGlobalBounds().width, Leaderboard::txtDisplay.getGlobalBounds().height) * .5f);
				this->core->getWindow().draw(Leaderboard::txtDisplay);

			}
		}
	}

	void Leaderboard::unload() {
		Score::enterLeaderboard = -1;
		Score::saveHighScores();
	}

	std::string Leaderboard::buildNameString() {
		std::string str = "___";
		for (int i = 0; i < 3; i++) {
			str[i] = (char)(this->selections[i] + 65);
		}

		return str;
	}
}