#include "Sparks.hpp"

Sparks::Sparks()
{
	this->dir = DOWN;
}

Sparks::Sparks(Core* _core, GameField* _field, sf::Vector2u _pos, Direction _dir):Ennemy(_core, _field, _pos)
{
	this->dir = _dir;
}

void Sparks::update()
{
	switch (this->dir)
	{
	case UP:
		this->pos.y--;
		break;
	case DOWN:
		this->pos.y++;
		break;
	case LEFT:
		this->pos.x--;
		break;
	case RIGHT:
		this->pos.x++;
		break;
	}

}

void Sparks::draw()
{
}
