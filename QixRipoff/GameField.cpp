#include "GameField.hpp"

const sf::Color clrUnclaimed = sf::Color::Transparent;
const sf::Color clrBlue = sf::Color(0, 125, 123, 255);
const sf::Color clrRed = sf::Color(146, 36, 16, 255);
const sf::Color clrStixBlue = sf::Color(0, 125, 123, 128);
const sf::Color clrStixRed = sf::Color(146, 36, 16, 128);
const sf::Color clrEdge = sf::Color::White;

GameField::GameField() {
	this->img.create(128U, 128U, sf::Color::Transparent);
	this->tex.create(128U, 128U);
	this->size = sf::Vector2u(128U, 128U);
}

GameField::GameField(sf::Vector2u _size) {
	this->img.create(_size.x, _size.y, sf::Color::Transparent);
	this->tex.create(_size.x, _size.y);
	this->size = _size;
}

void GameField::generateTexture() {
	this->tex.loadFromImage(this->img, sf::IntRect(0, 0, this->size.x, this->size.y));
}

void GameField::render(Window& _window) {
	this->spr.setTexture(this->tex);
	this->spr.setPosition(sf::Vector2f(128.f - (this->size.x * .5f), 96.f - (this->size.y * .5f)));
	_window.draw(this->spr);
}

FieldPixelState GameField::getPixel(sf::Vector2u _pos) {
	if (_pos.x < 0 || _pos.x >= this->size.x || _pos.y < 0 || _pos.y >= this->size.y) return CLAIMED_BLUE;
	sf::Color clr = this->img.getPixel(_pos.x, _pos.y);
	if (clr == clrUnclaimed)	return UNCLAIMED;
	if (clr == clrStixBlue)		return STIX_BLUE;
	if (clr == clrStixRed)		return STIX_RED;
	if (clr == clrBlue)			return CLAIMED_BLUE;
	if (clr == clrRed)			return CLAIMED_RED;
	if (clr == clrEdge)			return EDGE;
}

void GameField::setPixel(sf::Vector2u _pos, FieldPixelState _state) {
	if (_pos.x < 0 || _pos.x >= this->size.x || _pos.y < 0 || _pos.y >= this->size.y) return;
	sf::Color clr;
	if (_state == UNCLAIMED)	clr = clrUnclaimed;
	if (_state == STIX_BLUE)	clr = clrStixBlue;
	if (_state == STIX_RED)		clr = clrStixRed;
	if (_state == CLAIMED_BLUE)	clr = clrBlue;
	if (_state == CLAIMED_RED)	clr = clrRed;
	if (_state == EDGE)			clr = clrEdge;
	this->img.setPixel(_pos.x, _pos.y, clr);
}