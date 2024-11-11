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
	float timerMultiplier;
	
	sf::Vector2u posStixSource;
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

	void returnToEdge();
	void deathBlink();

	sf::Vector2u getPos() const { return this->pos; }
	float getTimerMove() const { return this->timerMove; }

	void setTimerMultiplier(float _timerMultiplier) { this->timerMultiplier = _timerMultiplier; }
	float getTimerMultiplier() const { return this->timerMultiplier; }

	void setLife(int _life) { this->life = _life; }
	int getLife() const { return this->life; }
};


