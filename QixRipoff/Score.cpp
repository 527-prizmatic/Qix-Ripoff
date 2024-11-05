#include <fstream>
#include "Score.hpp"
#include "Window.hpp"

sf::Text Score::txtDisplay;
sf::Font Score::txtFont;
std::vector<struct HighScore> Score::highscores;

void Score::preinit() {
	Score::txtFont.loadFromFile("../assets/fonts/qix-small.ttf");
	Score::txtDisplay.setFont(Score::txtFont);
	Score::txtDisplay.setCharacterSize(9);

	Score::highscores.reserve(5);
	for (int i = 0; i < 5; i++) {
		struct HighScore s = { std::string(), 0 };
		Score::highscores.push_back(s);
	}

	std::ofstream fo("../assets/highscores.dat", std::ios::out);
	if (!fo.fail()) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++) Score::highscores[i].name[j] = rand() % 26 + 65;
			Score::highscores[i].score = random32() % 1000000 + 1000000;
			fo.write(Score::highscores[i].name.c_str(), 3);
			fo.write((char*)&Score::highscores[i].score, sizeof(int));
			fo.write("\0", 1);
		}
		fo.close();
	}

	std::ifstream f("../assets/highscores.dat", std::ios::in);
	if (!f.fail()) {
		for (int i = 0; i < 5; i++) {
			char* nameBuf = (char*)calloc(3, sizeof(char));
			if (nameBuf == nullptr) continue;
			f.read(nameBuf, 3);
			Score::highscores[i].name = nameBuf;
			f.read((char*)&Score::highscores[i].score, sizeof(int));
			f.ignore(1);
			free(nameBuf);
		}
		f.close();
	}
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

void Score::addHighScore(std::string _name, int _score) {
	struct HighScore s = { _name, _score };
	Score::highscores.push_back(s);
}