#include "Score.hpp"
#include "Window.hpp"

const std::string highscoresSavePath = "../assets/highscores.dat";

// This exploded in the weirdest way possible, out it goes
//bool HighScore::operator==(const HighScore& _a, const HighScore& _b) {
//	bool namesOk = !_a.name.compare(_b.name);
//	bool scoresOk = _a.score == _b.score;
//	return namesOk && scoresOk;
//}

//bool HighScore::operator<(const HighScore& _a) { return this->score < _a.score; }

void Score::preinit() {
	Score::txtFont.loadFromFile("../assets/fonts/qix-small.ttf");
	Score::txtDisplay.setFont(Score::txtFont);
	Score::txtDisplay.setCharacterSize(9);

	Score::highscores.reserve(5);
//	Score::loadDefaultHighScores();
//	Score::saveHighScores();
	Score::loadHighScores();
	Score::printHighscores();
	Score::sortHighscores();
	Score::printHighscores();

	Score::enterLeaderboard = -1;
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
			HighScore score;

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
	Score::addHighScore("AAD", 10000);
	Score::addHighScore("AAE", 25000);
}

void Score::addHighScore(std::string _name, int _score) {
	HighScore s = { _name, _score };
	HighScore& newScore = s;
	Score::highscores.push_back(s);
	Score::sortHighscores();
	
	for (int i = 0; i < 4; i++) {
		if (Score::highscores[i].score == newScore.score) {
			Score::enterLeaderboard = i; break;
		}
		else Score::enterLeaderboard = -1;
	}

	if (Score::highscores.size() == 6) Score::highscores.erase(Score::highscores.begin() + 5);
	Score::printHighscores();
	
}

void Score::printHighscores() {
	for (std::vector<HighScore>::iterator i = Score::highscores.begin(); i != Score::highscores.end(); ++i) {
		std::cout << i->name << "   " << i->score << std::endl;
	}
}

void Score::sortHighscores() {
	// This exploded in the weirdest way possible, out it goes
	//	std::sort(Score::highscores.begin(), Score::highscores.end(), std::greater<HighScore>());

	for (int i = 1; i < Score::highscores.size(); i++) {
		int k = i;
		while (Score::highscores[k].score > Score::highscores[k - 1].score && k >= 1) {
			HighScore tmp = Score::highscores[k];
			Score::highscores[k] = Score::highscores[k - 1];
			Score::highscores[k - 1] = tmp;
			k--;
		}
	}
}