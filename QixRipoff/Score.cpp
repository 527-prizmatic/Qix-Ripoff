#include "Score.hpp"
#include "Window.hpp"

sf::Text Score::txtDisplay;
sf::Font Score::txtFont;

void Score::preinit() {
	Score::txtFont.loadFromFile("../assets/fonts/qix-small.ttf");
	Score::txtDisplay.setFont(Score::txtFont);
	Score::txtDisplay.setCharacterSize(9);
}

Score::Score() {
	this->score = 0;
}

void Score::render(Window& _w, sf::Vector2u _pos) {
	Score::txtDisplay.setPosition(sf::Vector2f(_pos));
	Score::txtDisplay.setString(std::to_string(this->score));
	_w.draw(Score::txtDisplay);
}