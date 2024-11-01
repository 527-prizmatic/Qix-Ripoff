#include "Player.hpp"


sf::RectangleShape rect;

Player::Player()
{
	this->core = nullptr;
	this->field = nullptr;
	this->pos = sf::Vector2u(0, 0);
	this->life = 0;
	this->timerMove = 0.f;
}

Player::Player(Core* _core, GameField* _field, sf::Vector2u _pos, int life)
{
	this->core = _core;
	this->field = _field;
	this->pos = _pos;
	this->life = life;
	this->timerMove = 0.f;
}

void Player::update()
{
	timerMove += tutil::getDelta();
	if (timerMove > 0.025f)
	{
		if (this->core->getKeyboard().held("Up"))
		{
			if (this->field->getPixel(this->pos + sf::Vector2u(0, -1)) == EDGE || this->core->getKeyboard().held("OK") || this->core->getKeyboard().held("Kaboom"))
			{
				if (this->core->getKeyboard().held("OK"))
				{
					pos.y -= 2;
					timerMove = 0.f;
				}
				else if (this->core->getKeyboard().held("Kaboom"))
				{
					pos.y -= 1;
					timerMove = 0.f;
				}
				else
				{
					pos.y -= 1;
					timerMove = 0.f;
				}
			}
		}
		else if (this->core->getKeyboard().held("Down"))
		{
			if (this->field->getPixel(this->pos + sf::Vector2u(0, 1)) == EDGE || this->core->getKeyboard().held("OK") || this->core->getKeyboard().held("Kaboom"))
			{
				if (this->core->getKeyboard().held("OK"))
				{
					pos.y += 2;
					timerMove = 0.f;
				}
				else if (this->core->getKeyboard().held("Kaboom"))
				{
					pos.y += 1;
					timerMove = 0.f;
				}
				else
				{
					pos.y += 1;
					timerMove = 0.f;
				}
			}
		}
		else if (this->core->getKeyboard().held("Left"))
		{
			if (this->field->getPixel(this->pos + sf::Vector2u(-1, 0)) == EDGE || this->core->getKeyboard().held("OK") || this->core->getKeyboard().held("Kaboom"))
			{
				if (this->core->getKeyboard().held("OK"))
				{
					pos.x -= 2;
					timerMove = 0.f;
				}
				else if (this->core->getKeyboard().held("Kaboom"))
				{
					pos.x -= 1;
					timerMove = 0.f;
				}
				else
				{
					pos.x -= 1;
					timerMove = 0.f;
				}
			}
		}
		else if (this->core->getKeyboard().held("Right"))
		{
			if (this->field->getPixel(this->pos + sf::Vector2u(1, 0)) == EDGE || this->core->getKeyboard().held("OK") || this->core->getKeyboard().held("Kaboom"))
			{
				if (this->core->getKeyboard().held("OK"))
				{
					pos.x += 2;
					timerMove = 0.f;
				}
				else if (this->core->getKeyboard().held("Kaboom"))
				{
					pos.x += 1;
					timerMove = 0.f;
				}
				else
				{
					pos.x += 1;
					timerMove = 0.f;
				}
			}
		}
	}
}

void Player::draw()
{
	rect.setSize(sf::Vector2f(10.f, 10.f));
	rect.setFillColor(sf::Color::Green);
	rect.setPosition(sf::Vector2f(pos));
	this->core->getWindow().draw(rect);
}
