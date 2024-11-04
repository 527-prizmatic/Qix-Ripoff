#include "Sparks.hpp"
#include "GameField.hpp"
#include "Player.hpp"

sf::RectangleShape rectangleSparks(sf::Vector2f(10, 10));

Sparks::Sparks()
{
	/*this->dir = DOWN;
	Sparks::sparks.push_back(*this);*/
}

Sparks::Sparks(Core* _core, GameField* _field, sf::Vector2u _pos, Direction _dir):Ennemy(_core, _field, _pos)
{
	this->dir = _dir;
	this->timerMove = 0.f;
}

void Sparks::update(GameField* _field, class Player* _plr)
{
	timerMove += tutil::getDelta();
	if (timerMove > 0.1)
	{
		sf::Vector2u posNext = this->pos;
		sf::Vector2u posNext2 = this->pos;
		if (this->dir == UP && this->field->getPixel(posNext) == EDGE)
		{
			timerMove = 0.f;
			posNext += sf::Vector2u(0, -1);
			posNext2 += sf::Vector2u(0, -2);
		}
		if (this->dir == DOWN)
		{
			timerMove = 0.f;
			posNext += sf::Vector2u(0, 1);
			posNext2 += sf::Vector2u(0, 2);
		}
		if (this->dir == LEFT)
		{
			timerMove = 0.f;
			posNext += sf::Vector2u(-1, 0);
			posNext2 += sf::Vector2u(-2, 0);
		}
		if (this->dir == RIGHT)
		{
			timerMove = 0.f;
			posNext += sf::Vector2u(1, 0);
			posNext2 += sf::Vector2u(2, 0);
		}
	}
}

void Sparks::draw(GameField* _field)
{
	rectangleSparks.setPosition(sf::Vector2f(this->pos + _field->getRenderOffset()));
	rectangleSparks.setFillColor(sf::Color::Red);
	this->core->getWindow().draw(rectangleSparks);
}
