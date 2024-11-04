#pragma once
#include "Ennemy.hpp"
#include "Core.hpp"

class GameField;
class Player;

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
	float timerMove;
public:
	Sparks();
	Sparks(Core* _core, GameField* _field, sf::Vector2u _pos, Direction _dir);
	void update(GameField* _field, class Player* _plr);
	void draw(GameField* _field);
};

