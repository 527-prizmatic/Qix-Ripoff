#include "GameField.hpp"
#include "resources/Textures.hpp"
#include "Qix.hpp"

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
	this->createOutline();
	this->generateTexture();

//	this->qixList.push_back(new Qix());
}

GameField::GameField(Core* _core, sf::Vector2u _size) {
	this->img.create(_size.x, _size.y, sf::Color::Transparent);
	this->tex.create(_size.x, _size.y);
	this->size = _size;
	this->createOutline();
	this->generateTexture();

//	this->qixList.push_back(new Qix(_core, this));
}

void GameField::update() {
//	for (std::list<Qix*>::iterator q = this->qixList.begin(); q != this->qixList.end(); ++q) {
//		(*q)->update(this);
//	}
}

void GameField::createOutline() {
	for (unsigned int i = 0; i < this->size.x; i++) {
		this->setPixel(sf::Vector2u(i, 0), EDGE);
		this->setPixel(sf::Vector2u(i, this->size.y - 1), EDGE);
	}
	for (unsigned int i = 0; i < this->size.y; i++) {
		this->setPixel(sf::Vector2u(0, i), EDGE);
		this->setPixel(sf::Vector2u(this->size.x - 1, i), EDGE);
	}
}

void GameField::generateTexture() {
	this->tex.loadFromImage(this->img, sf::IntRect(0, 0, this->size.x, this->size.y));
//	this->tex = Texture::getTexture("pavouka");
}

void GameField::render(Window& _window) {
	this->spr.setTexture(this->tex);
	this->spr.setPosition(sf::Vector2f(128.f, 112.f));
	this->spr.setOrigin(sf::Vector2f(this->size) * .5f);
	this->renderOffset = sf::Vector2u(sf::Vector2f(128.f, 112.f) - sf::Vector2f(this->size) * .5f);
	_window.draw(this->spr);

//	for (std::list<Qix*>::iterator q = this->qixList.begin(); q != this->qixList.end(); ++q) {
//		(*q)->draw(this);
//	}
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
	return CLAIMED_BLUE;
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

bool GameField::isValidMovement(sf::Vector2u _pos) {
	FieldPixelState top		= this->getPixel(sf::Vector2u(sf::Vector2i(_pos) + sf::Vector2i(0, -1)));
	FieldPixelState tl		= this->getPixel(sf::Vector2u(sf::Vector2i(_pos) + sf::Vector2i(-1, -1)));
	FieldPixelState left	= this->getPixel(sf::Vector2u(sf::Vector2i(_pos) + sf::Vector2i(-1, 0)));
	FieldPixelState bl		= this->getPixel(sf::Vector2u(sf::Vector2i(_pos) + sf::Vector2i(-1, 1)));
	FieldPixelState bottom	= this->getPixel(sf::Vector2u(sf::Vector2i(_pos) + sf::Vector2i(0, 1)));
	FieldPixelState br		= this->getPixel(sf::Vector2u(sf::Vector2i(_pos) + sf::Vector2i(1, 1)));
	FieldPixelState right	= this->getPixel(sf::Vector2u(sf::Vector2i(_pos) + sf::Vector2i(1, 0)));
	FieldPixelState tr		= this->getPixel(sf::Vector2u(sf::Vector2i(_pos) + sf::Vector2i(1, -1)));

	return top == UNCLAIMED || bottom == UNCLAIMED || left == UNCLAIMED || right == UNCLAIMED || tl == UNCLAIMED || bl == UNCLAIMED || br == UNCLAIMED || tr == UNCLAIMED;
}