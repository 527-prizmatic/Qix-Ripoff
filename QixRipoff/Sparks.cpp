#include "Sparks.hpp"
#include "Player.hpp"

sf::RectangleShape rectangleSparks(sf::Vector2f(7, 7));

Sparks::Sparks()
{
	this->dir = DOWN;
	this->timerMove = 0.f;
	this->timerChangeDir = 0.f;
}

Sparks::Sparks(Core* _core, GameField* _field, sf::Vector2u _pos, Direction _dir):Ennemy(_core, _field, _pos)
{
	this->dir = _dir;
	this->timerMove = 0.f;
	this->timerChangeDir = 0.f;
}

void Sparks::update(GameField* _field, class Player* _plr)
{
	timerMove += tutil::getDelta();
	timerChangeDir += tutil::getDelta();
	if (timerMove > 0.04f)
	{
		sf::Vector2u posNext = this->pos;
		sf::Vector2u posNext2 = this->pos;

		if (this->dir == UP)
		{
			timerMove = 0.f;
			posNext += sf::Vector2u(0, -1);
			posNext2 += sf::Vector2u(0, -2);
		}
		if (this->dir == DOWN )
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

		if (_field->getPixel(posNext2) == EDGE) {
			if (_field->isValidMovement(posNext2) || !_field->isValidMovement(this->pos)) {
				this->pos = posNext2;
			}
			else changeDirection(_field, this->pos);
		}
		else {
			changeDirection(_field, this->pos);
		}


	//	changeDirection(_field, posNext);
	}
	if (_plr->getTimerMove() > 0.f)
	{
		for (int i = 0; i < 49; i++) {
			sf::Vector2u vec(i % 7 - 3, i / 7 - 3);
			if (_plr->getPos() == this->pos + vec) {
				_field->replaceAll(STIX_BLUE, UNCLAIMED);
				_field->replaceAll(STIX_RED, UNCLAIMED);
				_plr->returnToEdge();
				_field->generateTexture();
				break;
			}
		}
	}
}

void Sparks::draw(GameField* _field)
{
	rectangleSparks.setPosition(sf::Vector2f(this->pos + _field->getRenderOffset()) - sf::Vector2f(3.f, 3.f));
	rectangleSparks.setFillColor(sf::Color::Red);
	this->core->getWindow().draw(rectangleSparks);
}

Direction Sparks::isThereIntersection(GameField* _field, sf::Vector2u _pos)
{
	if (this->timerChangeDir > 0.f)
	{
		if (this->dir == RIGHT)
		{
			if (_field->getPixel(_pos + sf::Vector2u(0, -1)) == EDGE)
			{
				return UP;
			}
			else if (_field->getPixel(_pos + sf::Vector2u(0, 1)) == EDGE)
			{
				return DOWN;
			}
		}
		else if (this->dir == LEFT)
		{
			if (_field->getPixel(_pos + sf::Vector2u(0, -1)) == EDGE)
			{
				return UP;
			}
			else if (_field->getPixel(_pos + sf::Vector2u(0, 1)) == EDGE)
			{
				return DOWN;
			}
		}
		else if (this->dir == UP)
		{
			if (_field->getPixel(_pos + sf::Vector2u(1, 0)) == EDGE)
			{
				return RIGHT;
			}
			else if (_field->getPixel(_pos + sf::Vector2u(-1, 0)) == EDGE)
			{
				return LEFT;
			}
		}
		else if (this->dir == DOWN)
		{
			if (_field->getPixel(_pos + sf::Vector2u(-1, 0)) == EDGE)
			{
				return LEFT;
			}
			else if (_field->getPixel(_pos + sf::Vector2u(1, 0)) == EDGE)
			{
				return RIGHT;
			}
		}
	}
	return NONEDIRECTION;
}

void Sparks::changeDirection(GameField* _field, sf::Vector2u _pos)
{
	if (isThereIntersection(_field, _pos) != NONEDIRECTION)
	{
		if (isThereIntersection(_field, _pos) == UP && this->dir != UP)
		{
			this->timerChangeDir = 0.f;
			this->dir = UP;
		}
		if (isThereIntersection(_field, _pos) == DOWN && this->dir != DOWN)
		{
			this->timerChangeDir = 0.f;
			this->dir = DOWN;
		}
		if (isThereIntersection(_field, _pos) == LEFT && this->dir != LEFT)
		{
			this->timerChangeDir = 0.f;
			this->dir = LEFT;
		}
		if (isThereIntersection(_field, _pos) == RIGHT && this->dir != RIGHT)
		{
			this->timerChangeDir = 0.f;
			this->dir = RIGHT;
		}
	}
}
