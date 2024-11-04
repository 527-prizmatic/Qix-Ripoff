#pragma once
#include "Core.hpp"
#include "GameField.hpp"
#include"toolbox/toolbox.hpp"


class Ennemy
{
protected:
	Core* core;
	GameField* field;
	sf::Vector2u pos;
	float timerMove;
public:
	Ennemy();
	Ennemy(Core* _core, GameField* _field, sf::Vector2u _pos);
	virtual void update(GameField* _field, class Player* _plr) = 0;
	virtual void draw(GameField* _field) = 0;
};

