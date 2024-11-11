#pragma once
#include "Core.hpp"
#include"toolbox/toolbox.hpp"

class GameField;

class Bonus
{
	protected:
	Core* core;
	GameField* field;
	sf::Vector2u pos;

public:
	Bonus();
	Bonus(Core* _core, GameField* _field, sf::Vector2u _pos);
	virtual void update(GameField* _field, class Player* _plr) = 0;
	virtual void draw(GameField* _field) = 0;
};

