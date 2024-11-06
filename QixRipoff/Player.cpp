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

	bool slow = false;
	if (this->core->getKeyboard().held("Kaboom")) slow = true;
	if (!this->isDrawing) slow = false;

	if ((timerMove > 0.05f && !slow) || (timerMove > 0.1f && slow))
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
		if (((this->field->getPixel(posNext) & TYPE_MASK) == STIX || (this->field->getPixel(posNext2) & TYPE_MASK) == STIX) == STIX && this->pos != posNext) {
			this->field->replaceAll(STIX_BLUE, UNCLAIMED);
			this->field->replaceAll(STIX_RED, UNCLAIMED);
			this->returnToEdge();
			this->field->generateTexture();
		}
		else {
			if (!this->isDrawing) {
				this->posStixSource = this->pos;
			}
			if (this->core->getKeyboard().held("OK")) {
				if ((this->field->getPixel(posNext2) == EDGE || this->field->getPixel(posNext2) == UNCLAIMED) && this->field->isValidMovement(posNext2)) {
					this->posPrev = posNext;
					this->pos = posNext2;
				}
			}
			else if (this->core->getKeyboard().held("Kaboom")) {
				if ((this->field->getPixel(posNext2) == EDGE || this->field->getPixel(posNext2) == UNCLAIMED) && this->field->isValidMovement(posNext2)) {
					this->posPrev = posNext;
					this->pos = posNext2;
				}
			}
			else {
				if (this->field->getPixel(posNext2) == EDGE && this->field->isValidMovement(posNext2)) {
					this->posPrev = posNext;
					this->pos = posNext2;
				}
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

	this->pos.x - this->pos.x % 2;
	this->pos.y - this->pos.y % 2;

	if (this->life <= 0) {
		this->core->requestStateChange(MENU);
	}
}

void Player::draw()
{
	if (this->timerMove >= 0.f || std::fmod(std::abs(this->timerMove), .25f) < .125f) {
		renderSpr.setTexture(Texture::getTexture("marker"));
		renderSpr.setPosition(sf::Vector2f(this->pos + this->field->getRenderOffset()) - sf::Vector2f(3.f, 3.f));
		this->core->getWindow().draw(renderSpr);
	}
}

void Player::drawStix() {
	this->field->setPixel(this->pos, this->isDrawingRed ? STIX_RED : STIX_BLUE);
	this->field->setPixel(this->posPrev, this->isDrawingRed ? STIX_RED : STIX_BLUE);
	this->field->generateTexture();
}

void Player::claimArea() {
	this->isDrawing = false;
	sf::Vector2u pos = this->posPrev;
	sf::Vector2u adj1, adj2;
	GameField::SearchDir dir;

	if (this->field->getPixel(pos + sf::Vector2u(1, 0)) == UNCLAIMED && this->field->getPixel(pos - sf::Vector2u(1, 0)) == UNCLAIMED) {
		adj1 = pos + sf::Vector2u(1, 0);
		adj2 = pos - sf::Vector2u(1, 0);
		dir = GameField::SearchDir::HORIZONTAL;
	}

	else if (this->field->getPixel(pos + sf::Vector2u(0, 1)) == UNCLAIMED && this->field->getPixel(pos - sf::Vector2u(0, 1)) == UNCLAIMED) {
		adj1 = pos + sf::Vector2u(0, 1);
		adj2 = pos - sf::Vector2u(0, 1);
		dir = GameField::SearchDir::VERTICAL;
	}

	if (this->isDrawingRed) {
		this->field->replaceAll(STIX_RED, EDGE);
		if (this->field->countPathCrossings(adj1, this->field->getQixPos(0), dir) % 2 == 1) this->field->iterativeFill(adj1, FieldPixelState::RED);
		else if (this->field->countPathCrossings(adj2, this->field->getQixPos(0), dir) % 2 == 1) this->field->iterativeFill(adj2, FieldPixelState::RED);
	}
	else {
		this->field->replaceAll(STIX_BLUE, EDGE);
		if (this->field->countPathCrossings(adj1, this->field->getQixPos(0), dir) % 2 == 1) this->field->iterativeFill(adj1, FieldPixelState::BLUE);
		else if (this->field->countPathCrossings(adj2, this->field->getQixPos(0), dir) % 2 == 1) this->field->iterativeFill(adj2, FieldPixelState::BLUE);
	}
	this->field->generateTexture();
}

void Player::returnToEdge() {
	this->life--;
	this->pos = this->posStixSource;
	this->isDrawing = false;
	this->deathBlink();
}

void Player::deathBlink() {
	this->timerMove = -1.5f;
}