#include "Player.hpp"
#include "resources/Textures.hpp"

sf::Sprite Player::renderSpr;

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
		sf::Vector2u posNext = this->pos;
		sf::Vector2u posNext2 = this->pos;

		if (this->core->getKeyboard().held("Up"))
		{
			timerMove = 0.f;
			posNext += sf::Vector2u(0, -1);
			posNext2 += sf::Vector2u(0, -2);
		}
		else if (this->core->getKeyboard().held("Down"))
		{
			timerMove = 0.f;
			posNext += sf::Vector2u(0, 1);
			posNext2 += sf::Vector2u(0, 2);
		}
		else if (this->core->getKeyboard().held("Left"))
		{
			timerMove = 0.f;
			posNext += sf::Vector2u(-1, 0);
			posNext2 += sf::Vector2u(-2, 0);
		}
		else if (this->core->getKeyboard().held("Right"))
		{
			timerMove = 0.f;
			posNext += sf::Vector2u(1, 0);
			posNext2 += sf::Vector2u(2, 0);
		}

		if (this->core->getKeyboard().held("OK")) {
			if ((this->field->getPixel(posNext2) == EDGE || this->field->getPixel(posNext2) == UNCLAIMED) && this->field->isValidMovement(posNext2)) {
				this->pos = posNext2;
			}
			else if ((this->field->getPixel(posNext) == EDGE || this->field->getPixel(posNext) == UNCLAIMED) && this->field->isValidMovement(posNext)) {
				this->pos = posNext;
			}
		}
		else if (this->core->getKeyboard().held("Kaboom")) {
			if ((this->field->getPixel(posNext) == EDGE || this->field->getPixel(posNext) == UNCLAIMED) && this->field->isValidMovement(posNext)) {
				this->pos = posNext;
			}
		}
		else {
			if (this->field->getPixel(posNext) == EDGE && this->field->isValidMovement(posNext)) {
				this->pos = posNext;
			}
		}
	}
}

void Player::draw()
{
	renderSpr.setTexture(Texture::getTexture("marker"));
	renderSpr.setPosition(sf::Vector2f(this->pos + this->field->getRenderOffset()) - sf::Vector2f(3.f, 3.f));
	this->core->getWindow().draw(renderSpr);
}
