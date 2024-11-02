#pragma once
#include "Core.hpp"
#include "GameField.hpp"
#include"toolbox/toolbox.hpp"

class Player{
private:
	Core* core;
	GameField* field;
	sf::Vector2u pos;
	sf::Vector2u posPrev;
	float timerMove;
	int life;
	
	bool isDrawing;
	bool isDrawingRed;

	static sf::Sprite renderSpr;

	void drawStix();
	void claimArea();
public:
	Player();
	Player(Core* _core, GameField* _field, sf::Vector2u _pos, int _life);

	void update();
	void draw();
};


