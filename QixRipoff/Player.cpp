#include "Player.hpp"
#include "resources/Textures.hpp"

sf::Sprite Player::renderSpr;

Player::Player()
{
	this->core = nullptr;
	this->field = nullptr;
	this->pos = sf::Vector2u(0, 0);
	this->posPrev = sf::Vector2u(0, 0);
	this->life = 0;
	this->timerMove = 0.f;
	this->isDrawing = false;
	this->isDrawingRed = false;
}

Player::Player(Core* _core, GameField* _field, sf::Vector2u _pos, int life)
{
	this->core = _core;
	this->field = _field;
	this->pos = _pos;
	this->posPrev = _pos;
	this->life = life;
	this->timerMove = 0.f;
	this->isDrawing = false;
	this->isDrawingRed = false;
}

void Player::update()
{
	/// FIXME REVERT FAST SPEED TO NORMAL AND MAKE TIMERMOVE VARY INSTEAD
	timerMove += tutil::getDelta();
	if (timerMove > 0.05f)
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
			if ((this->field->getPixel(posNext) == EDGE || this->field->getPixel(posNext) == UNCLAIMED) && this->field->isValidMovement(posNext)) {
				this->posPrev = this->pos;
				this->pos = posNext;
			}
		}
		else if (this->core->getKeyboard().held("Kaboom")) {
			if ((this->field->getPixel(posNext) == EDGE || this->field->getPixel(posNext) == UNCLAIMED) && this->field->isValidMovement(posNext)) {
				this->posPrev = this->pos;
				this->pos = posNext;
			}
		}
		else {
			if (this->field->getPixel(posNext) == EDGE && this->field->isValidMovement(posNext)) {
				this->posPrev = this->pos;
				this->pos = posNext;
			}
		}
	}

	if (this->field->getPixel(this->pos) == EDGE) {
		if (this->isDrawing) {
			this->drawStix();
			this->claimArea();
		}
		this->isDrawing = false;
		this->isDrawingRed = true;
	}
	else if (this->field->getPixel(this->pos) == UNCLAIMED) {
		this->isDrawing = true;
		this->drawStix();
		if (this->core->getKeyboard().held("OK")) {
			this->isDrawingRed = false;
			this->field->replaceAll(STIX_RED, STIX_BLUE);
			this->field->generateTexture();
		}
	}
}

void Player::draw()
{
	renderSpr.setTexture(Texture::getTexture("marker"));
	renderSpr.setPosition(sf::Vector2f(this->pos + this->field->getRenderOffset()) - sf::Vector2f(3.f, 3.f));
	this->core->getWindow().draw(renderSpr);
}

void Player::drawStix() {
	this->field->setPixel(this->pos, this->isDrawingRed ? STIX_RED : STIX_BLUE);
	this->field->generateTexture();
}

void Player::claimArea() {
	sf::Vector2u bogusQixPos(50U, 50U);

	this->isDrawing = false;
	sf::Vector2u pos = this->posPrev;
	sf::Vector2u adj1, adj2;
	GameField::SearchDir dir;

	if (this->field->getPixel(pos + sf::Vector2u(1, 0)) == UNCLAIMED && this->field->getPixel(pos - sf::Vector2u(1, 0)) == UNCLAIMED) {
		adj1 = pos + sf::Vector2u(1, 0);
		adj2 = pos - sf::Vector2u(1, 0);
		dir = GameField::SearchDir::HORIZONTAL;
	}

	if (this->field->getPixel(pos + sf::Vector2u(0, 1)) == UNCLAIMED && this->field->getPixel(pos - sf::Vector2u(0, 1)) == UNCLAIMED) {
		adj1 = pos + sf::Vector2u(0, 1);
		adj2 = pos - sf::Vector2u(0, 1);
		dir = GameField::SearchDir::VERTICAL;
	}

	if (this->isDrawingRed) {
		this->field->replaceAll(STIX_RED, EDGE);
		if (this->field->countPathCrossings(adj1, bogusQixPos, dir) % 2 == 1) this->field->iterativeFill(adj1, FieldPixelState::RED);
		if (this->field->countPathCrossings(adj2, bogusQixPos, dir) % 2 == 1) this->field->iterativeFill(adj2, FieldPixelState::RED);
	}
	else {
		this->field->replaceAll(STIX_BLUE, EDGE);
		if (this->field->countPathCrossings(adj1, bogusQixPos, dir) % 2 == 1) this->field->iterativeFill(adj1, FieldPixelState::BLUE);
		if (this->field->countPathCrossings(adj2, bogusQixPos, dir) % 2 == 1) this->field->iterativeFill(adj2, FieldPixelState::BLUE);
	}
	this->field->generateTexture();
}