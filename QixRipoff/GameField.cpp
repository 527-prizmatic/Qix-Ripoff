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
	this->img.create(127U, 127U, sf::Color::Transparent);
	this->tex.create(127U, 127U);
	this->size = sf::Vector2u(127U, 127U);
	this->createOutline();
	this->generateTexture();

	this->qixList.push_back(new Qix());
}

GameField::GameField(Core* _core, sf::Vector2u _size) {
	this->img.create(_size.x, _size.y, sf::Color::Transparent);
	this->tex.create(_size.x, _size.y);
	this->size = _size;
	this->createOutline();
	this->generateTexture();

	this->qixList.push_back(new Qix(_core, this));
}

void GameField::update(Player* _plr) {
	for (std::list<Qix*>::iterator q = this->qixList.begin(); q != this->qixList.end(); ++q) {
		(*q)->update(this, _plr);
	}
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
}

void GameField::render(Window& _window) {
	this->spr.setTexture(this->tex);
	this->spr.setPosition(sf::Vector2f(128.f, 112.f));
	this->spr.setOrigin(sf::Vector2f(this->size) * .5f);
	this->renderOffset = sf::Vector2u(sf::Vector2f(128.f, 112.f) - sf::Vector2f(this->size) * .5f);
	_window.draw(this->spr);

	for (std::list<Qix*>::iterator q = this->qixList.begin(); q != this->qixList.end(); ++q) {
		(*q)->draw(this);
	}
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

bool GameField::replaceAll(FieldPixelState _state_old, FieldPixelState _state_new) {
	bool replaced = false;
	for (int y = 0; y < this->size.y; y++) {
		for (int x = 0; x < this->size.x; x++) {
			if (this->getPixel(sf::Vector2u(x, y)) == _state_old) {
				this->setPixel(sf::Vector2u(x, y), _state_new);
				replaced = true;
			}
		}
	}
	return replaced;
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

int GameField::countPathCrossings(sf::Vector2u _src, sf::Vector2u _dest, enum SearchDir _dir) {
	int crossings = 0;

	if (_dir == HORIZONTAL) {
		while (_src.x != _dest.x) {
			if (_src.x < _dest.x) _src.x++;
			else _src.x--;
			if (this->getPixel(_src) == EDGE) crossings++;
		}
		while (_src.y != _dest.y) {
			if (_src.y < _dest.y) _src.y++;
			else _src.y--;
			if (this->getPixel(_src) == EDGE) crossings++;
		}
	}

	if (_dir == VERTICAL) {
		while (_src.y != _dest.y) {
			if (_src.y < _dest.y) _src.y++;
			else _src.y--;
			if (this->getPixel(_src) == EDGE) crossings++;
		}
		while (_src.x != _dest.x) {
			if (_src.x < _dest.x) _src.x++;
			else _src.x--;
			if (this->getPixel(_src) == EDGE) crossings++;
		}
	}

	return crossings;
}

void GameField::iterativeFill(sf::Vector2u _pos, FieldPixelState _clr) {
	std::list<sf::Vector2u> posToFill;
	std::list<sf::Vector2u> posFilled;
	_clr = (FieldPixelState)(CLAIMED | (_clr & CLR_MASK));
	posToFill.push_back(_pos);

	while (1) {
		bool filled = false;
		
		for (sf::Vector2u coord : posToFill) {
			if (this->getPixel(coord) == UNCLAIMED) {
				this->setPixel(coord, _clr);
				filled = true;
				if (this->getPixel(coord + sf::Vector2u(1, 0)) == UNCLAIMED)
					posFilled.push_back(coord + sf::Vector2u(1, 0));
				if (this->getPixel(coord - sf::Vector2u(1, 0)) == UNCLAIMED)
					posFilled.push_back(coord - sf::Vector2u(1, 0));
				if (this->getPixel(coord + sf::Vector2u(0, 1)) == UNCLAIMED)
					posFilled.push_back(coord + sf::Vector2u(0, 1));
				if (this->getPixel(coord - sf::Vector2u(0, 1)) == UNCLAIMED)
					posFilled.push_back(coord - sf::Vector2u(0, 1));
			}
		}

		if (!filled) break;
		posToFill = std::list<sf::Vector2u>(posFilled);
		posFilled.clear();
	}
}

sf::Vector2u GameField::getQixPos(int _id) {
	int i = 0;
	for (std::list<Qix*>::iterator q = this->qixList.begin(); q != this->qixList.end(); ++q) {
		if (i == _id) return (*q)->getPos();
		i++;
	}
}