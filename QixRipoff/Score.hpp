#pragma once
#include "toolbox/toolbox.hpp"

class Score {
private:
	int score;

	static sf::Text txtDisplay;
	static sf::Font txtFont;

public:
	static void preinit();
	Score();

	void render(class Window& _w, sf::Vector2u _pos);

	void addScore(const int _val) { this->score += _val; }
	int getScore() const { return this->score; }
};