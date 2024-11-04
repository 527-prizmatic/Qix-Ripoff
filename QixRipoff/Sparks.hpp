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
	RIGHT,
	NONEDIRECTION
};

class Sparks : public Ennemy
{
private:
	Direction dir;
	float timerMove;
	float timerChangeDir;
public:
	Sparks();
	Sparks(Core* _core, GameField* _field, sf::Vector2u _pos, Direction _dir);
	void update(GameField* _field, class Player* _plr);
	void draw(GameField* _field);

	Direction isThereIntersection(GameField* _field, sf::Vector2u _pos);
	void changeDirection(GameField* _field, sf::Vector2u _pos);
};

