#include <fstream>
#include "Score.hpp"
#include "Window.hpp"

const std::string highscoresSavePath = "../assets/highscores.dat";

sf::Text Score::txtDisplay;
sf::Font Score::txtFont;
std::vector<struct HighScore> Score::highscores;

void Score::preinit() {
	Score::txtFont.loadFromFile("../assets/fonts/qix-small.ttf");
	Score::txtDisplay.setFont(Score::txtFont);
	Score::txtDisplay.setCharacterSize(9);

	Score::highscores.reserve(5);
//	Score::loadDefaultHighScores();
//	Score::saveHighScores();
	Score::loadHighScores();
	Score::printHighscores();
}

Score::Score() {
	this->score = 0;
}

void Score::init() {

}

void Score::render(Window& _w, sf::Vector2u _pos) {
	Score::txtDisplay.setPosition(sf::Vector2f(_pos));
	Score::txtDisplay.setString(std::to_string(this->score));
	_w.draw(Score::txtDisplay);
}



void Score::saveHighScores() {
	std::ofstream fo(highscoresSavePath, std::ios::out);
	if (!fo.fail()) {
		for (std::vector<HighScore>::iterator i = Score::highscores.begin(); i != Score::highscores.end(); ++i) {
			fo.write(i->name.c_str(), 3);
			fo.write((char*)&i->score, sizeof(int));
			fo.write("\0", 1);
		}
		fo.close();
	}
}

void Score::loadHighScores() {
	std::ifstream f(highscoresSavePath, std::ios::in);
	if (!f.fail()) {
		char* nameBuf = (char*)calloc(4, sizeof(char));
		for (int i = 0; i < 5; i++) {
			struct HighScore score;

			if (nameBuf == nullptr) continue;
			f.read(nameBuf, 3);
			score.name = nameBuf;
			f.read((char*)&score.score, sizeof(int));
			f.ignore(1);

			Score::highscores.push_back(score);
		}
		free(nameBuf);
		f.close();
	}
}

void Score::loadDefaultHighScores() {
	Score::highscores.clear();
	Score::addHighScore("AAA", 100000);
	Score::addHighScore("AAB", 75000);
	Score::addHighScore("AAC", 50000);
	Score::addHighScore("AAD", 25000);
	Score::addHighScore("AAE", 10000);
}

void Score::addHighScore(std::string _name, int _score) {
	struct HighScore s = { _name, _score };
	Score::highscores.push_back(s);
}

void Score::printHighscores() {
	for (std::vector<HighScore>::iterator i = Score::highscores.begin(); i != Score::highscores.end(); ++i) {
		std::cout << i->name << "   " << i->score << std::endl;
	}
}