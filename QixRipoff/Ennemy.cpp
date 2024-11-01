#include "Ennemy.hpp"

Ennemy::Ennemy()
{
	this->core = nullptr;
	this->field = nullptr;
	this->pos = sf::Vector2u(0, 0);
	this->timerMove = 0.f;
}

Ennemy::Ennemy(Core* _core, GameField* _field, sf::Vector2u _pos)
{
	this->core = _core;
	this->field = _field;
	this->pos = _pos;
	this->timerMove = 0.f;
}
