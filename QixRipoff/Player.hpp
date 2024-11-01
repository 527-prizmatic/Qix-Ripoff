#pragma once
#include "Core.hpp"
#include "GameField.hpp"
#include"toolbox/toolbox.hpp"

class Player{
private:
	Core* core;
	GameField* field;
	sf::Vector2u pos;
	float timerMove;
	int life;

	static sf::Sprite renderSpr;
public:
	Player();
	Player(Core* _core, GameField* _field, sf::Vector2u _pos, int _life);

	void update();
	void draw();
};


