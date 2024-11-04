#pragma once
#include "toolbox/toolbox.hpp"
#include "GameField.hpp"
#include "Ennemy.hpp"
#include "Core.hpp"


enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Sparks : public Ennemy
{
private:
	Direction dir;
	static std::list<Sparks> sparks;
public:
	Sparks();
	Sparks(Core* _core, GameField* _field, sf::Vector2u _pos, Direction _dir);
	void update();
	void draw();

	sf::Vector2u getPos() { return this->pos; }
	void setPos(sf::Vector2u _pos) { this->pos = _pos; }
};

