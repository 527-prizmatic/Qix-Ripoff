#include "Bonus.hpp"

Bonus::Bonus()
{
	this->core = nullptr;
	this->field = nullptr;
	this->pos = sf::Vector2u(0, 0);
}

Bonus::Bonus(Core* _core, GameField* _field, sf::Vector2u _pos)
{
	this->core = _core;
	this->field = _field;
	this->pos = _pos;
}
