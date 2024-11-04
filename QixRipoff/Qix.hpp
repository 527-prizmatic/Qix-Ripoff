#pragma once
#include <deque>
#include "Core.hpp"
#include "Ennemy.hpp"

class GameField;
class Ennemy;

sf::Color hsl_to_rgb(sf::Color _hsl);

class Qix : public Ennemy {
private:
	float lifetime;
	sf::Vector2f absPos;
	sf::Vector2f direction;
	float timerDirChange;
	float angle;
	float timerAngleChange;
	float hue;
	sf::Color clr;
	float timerColorChange;
	std::deque<sf::Vector2u> afterimagesPos;
	std::deque<float> afterimagesAngle;
	std::deque<sf::Color> afterimagesColor;
	float timerAfterimages;
	static sf::VertexArray renderVA;

public:
	Qix();
	Qix(Core* _core, GameField* _field);

	void update(GameField* _field, class Player* _plr);
	void draw(GameField* _field);

	sf::Vector2u getPos() const { return this->pos; }
};