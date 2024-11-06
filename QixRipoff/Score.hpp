#pragma once
#include "toolbox/toolbox.hpp"

/// Mycelium
struct HighScore {
	std::string name;
	int score;
};

class Score {
private:
	int score;

	static sf::Text txtDisplay;
	static sf::Font txtFont;
	static std::vector<struct HighScore> highscores;

public:
	static void preinit();
	Score();

	void init();
	void render(class Window& _w, sf::Vector2u _pos);

	void addScore(const int _val) { this->score += _val; }
	int getScore() const { return this->score; }

	void addHighScore(std::string _name, int _score);
};