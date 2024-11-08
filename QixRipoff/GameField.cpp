#include "GameField.hpp"
#include "resources/Textures.hpp"
#include "Qix.hpp"
#include "Sparks.hpp"
#include "Score.hpp"

const sf::Color clrUnclaimed = sf::Color::Transparent;
const sf::Color clrBlue = sf::Color(0, 125, 123, 255);
const sf::Color clrRed = sf::Color(146, 36, 16, 255);
const sf::Color clrStixBlue = sf::Color(0, 125, 123, 128);
const sf::Color clrStixRed = sf::Color(146, 36, 16, 128);
const sf::Color clrEdge = sf::Color::White;
const sf::Color clrDebug = sf::Color(0, 255, 0, 32);

GameField::GameField() {
	this->img.create(127U, 127U, sf::Color::Transparent);
	this->tex.create(127U, 127U);
	this->size = sf::Vector2u(127U, 127U);
	this->pixelCount = (this->size.x - 2) * (this->size.y - 2);
	this->pixelsClaimed = 0;
	this->timerSparkSpawn = 0.f;
	this->createOutline();
	this->generateTexture();
	this->qixList.push_back(new Qix());
}

GameField::GameField(Core* _core, sf::Vector2u _size, Score* _score) {
	this->img.create(_size.x, _size.y, sf::Color::Transparent);
	this->tex.create(_size.x, _size.y);
	this->size = _size;
	this->pixelCount = (this->size.x - 2) * (this->size.y - 2);
	this->pixelsClaimed = 0;
	this->timerSparkSpawn = 0.f;
	this->score = _score;
	this->createOutline();
	this->generateTexture();
	this->sparksList.push_back(new Sparks(_core, this, sf::Vector2u(this->size.x / 2, 0), LEFT));
	this->sparksList.push_back(new Sparks(_core, this, sf::Vector2u(this->size.x / 2, 0), RIGHT));
	this->qixList.push_back(new Qix(_core, this));
}

void GameField::update(Core* _core, Player* _plr) 
{
	this->timerSparkSpawn += tutil::getDelta();
	if (this->timerSparkSpawn >= 20.f) {
		this->timerSparkSpawn = 0.f;
		this->sparksList.push_back(new Sparks(_core, this, sf::Vector2u(this->size.x / 2, 0), LEFT));
		this->sparksList.push_back(new Sparks(_core, this, sf::Vector2u(this->size.x / 2, 0), RIGHT));
	}

	for (std::list<Qix*>::iterator q = this->qixList.begin(); q != this->qixList.end(); ++q) {
		(*q)->update(this, _plr);
	}
	for (std::list<Sparks*>::iterator s = this->sparksList.begin(); s != this->sparksList.end(); ++s) 
	{
		(*s)->update(this, _plr);
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

	this->pixelsClaimed = 0;
	for (unsigned int i = 1; i < this->size.x - 1; i++) {
		for (unsigned int j = 1; j < this->size.y - 1; j++) {
			FieldPixelState pxl = this->getPixel(sf::Vector2u(i, j));
			if ((pxl != UNCLAIMED) && ((pxl & TYPE_MASK) != STIX)) this->pixelsClaimed++;
		}
	}
}

void GameField::render(Window& _window) {
	this->spr.setTexture(this->tex);
	this->spr.setPosition(sf::Vector2f(128.5f, 112.5f));
	this->spr.setOrigin(sf::Vector2f(this->size) * .5f);
	this->renderOffset = sf::Vector2u(sf::Vector2f(128.5f, 112.5f) - sf::Vector2f(this->size) * .5f);
	_window.draw(this->spr);
	for (std::list<Qix*>::iterator q = this->qixList.begin(); q != this->qixList.end(); ++q) {
		(*q)->draw(this);
	}
	for (std::list<Sparks*>::iterator s = this->sparksList.begin(); s != this->sparksList.end(); ++s) {
		(*s)->draw(this);
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
	if (clr == clrDebug)		return DEBUG;
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
	if (_state == DEBUG)		clr = clrDebug;
	this->img.setPixel(_pos.x, _pos.y, clr);
}

bool GameField::replaceAll(FieldPixelState _state_old, FieldPixelState _state_new) {
	bool replaced = false;
	for (unsigned int y = 0; y < this->size.y; y++) {
		for (unsigned int x = 0; x < this->size.x; x++) {
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
	bool isClaim = false;

	_dest.x = _dest.x / 2 * 2 + 1;
	_dest.y = _dest.y / 2 * 2 + 1;

	if (_dir == HORIZONTAL) {
		while (_src.x != _dest.x) {
			if (_src.x < _dest.x) _src.x++;
			else _src.x--;
			if (this->getPixel(_src) == EDGE && !isClaim) crossings++;
			if ((this->getPixel(_src) & TYPE_MASK) == CLAIMED) isClaim = true;
			if (this->getPixel(_src) == UNCLAIMED) {
				if (isClaim) crossings++;
				isClaim = false;
			}
		}
		while (_src.y != _dest.y) {
			if (_src.y < _dest.y) _src.y++;
			else _src.y--;
			if (this->getPixel(_src) == EDGE && !isClaim) crossings++;
			if ((this->getPixel(_src) & TYPE_MASK) == CLAIMED) isClaim = true;
			if (this->getPixel(_src) == UNCLAIMED) {
				if (isClaim) crossings++;
				isClaim = false;
			}
		}
	}

	if (_dir == VERTICAL) {
		while (_src.y != _dest.y) {
			if (_src.y < _dest.y) _src.y++;
			else _src.y--;
			if (this->getPixel(_src) == EDGE && !isClaim) crossings++;
			if ((this->getPixel(_src) & TYPE_MASK) == CLAIMED) isClaim = true;
			if (this->getPixel(_src) == UNCLAIMED) {
				if (isClaim) crossings++;
				isClaim = false;
			}
		}
		while (_src.x != _dest.x) {
			if (_src.x < _dest.x) _src.x++;
			else _src.x--;
			if (this->getPixel(_src) == EDGE && !isClaim) crossings++;
			if ((this->getPixel(_src) & TYPE_MASK) == CLAIMED) isClaim = true;
			if (this->getPixel(_src) == UNCLAIMED) {
				if (isClaim) crossings++;
				isClaim = false;
			}
		}
	}

	return crossings;
}

bool GameField::pathfindDetection(sf::Vector2u _src, sf::Vector2u _dest) {
	std::list<sf::Vector2u> posToSearch;
	std::list<sf::Vector2u> posSearched;
	std::list<sf::Vector2u> posWillSearch;
	_dest = sf::Vector2u(_dest.x + ((_dest.x + 1) % 2), _dest.y + ((_dest.y + 1) % 2));
	posToSearch.push_back(_src);

	/// Used to check how close to the Qix the nearest valid point found was
	int shortestDist = 100000000;

	while (1) {
		/// Used to check if any progress could be made on a given pass
		bool filled = false;

		int iterator = 0;
		for (sf::Vector2u coord : posToSearch) {
			if (coord == _dest) return true; /// Stop everything immediately if we reached the requested coordinate
			else {
				filled = true;
				posSearched.push_front(coord);
			//	this->setPixel(coord, DEBUG);

				int dist = (coord.x - _dest.x) * (coord.x - _dest.x) + (coord.y - _dest.y) * (coord.y - _dest.y);
				if (dist > shortestDist * 6) continue; /// Paths that wander too far from the Qix are simply eliminated
				if (dist < shortestDist) shortestDist = dist;

				/// As all player movement is snapped on a 2x2 pixel grid, two arrays of vectors are used.
				/// One is used to detect if the next point on the player's movement grid is accessible at all via pathfinding...
				std::array<sf::Vector2u, 4> posNext{{
					coord + sf::Vector2u(1, 0),
					coord - sf::Vector2u(1, 0),
					coord + sf::Vector2u(0, 1),
					coord - sf::Vector2u(0, 1)
				}};

				/// ...the other for adding the next point to the search list.
				std::array<sf::Vector2u, 4> posNext2{ {
					coord + sf::Vector2u(2, 0),
					coord - sf::Vector2u(2, 0),
					coord + sf::Vector2u(0, 2),
					coord - sf::Vector2u(0, 2)
				} };


				for (int i = 0; i < 4; i++) {
					if (this->getPixel(posNext[i]) == UNCLAIMED) { /// Is that pixel an empty pixel?
						bool alreadySearched = false;

						for (sf::Vector2u s : posWillSearch) {
							if (s == posNext2[i]) { /// Is that pixel already on the to-do list?
								alreadySearched = true;
								break;
							}
						}

						if (!alreadySearched) {
							for (sf::Vector2u s : posToSearch) {
								if (s == posNext2[i]) { /// Are we already going to scan this pixel on this pass?
									alreadySearched = true;
									break;
								}
							}

							if (!alreadySearched) {
								for (sf::Vector2u s : posSearched) {
									if (s == posNext2[i]) { /// Did we already scan it? (computationally heavy, better do it as late as possible)
										alreadySearched = true;
										break;
									}
								}

								/// If none of that is true, search that pixel on the next pass
								if (!alreadySearched) posWillSearch.push_back(posNext2[i]);
							}
						}
					}
				}
			}

			iterator++;
		}

		if (!filled) break;
		posToSearch.clear();
		posToSearch = std::list<sf::Vector2u>(posWillSearch);
		posWillSearch.clear();
	}

	return false;
}

void GameField::iterativeFill(sf::Vector2u _pos, FieldPixelState _clr) {
	std::list<sf::Vector2u> posToFill;
	std::list<sf::Vector2u> posFilled;
	_clr = (FieldPixelState)(CLAIMED | (_clr & CLR_MASK));
	posToFill.push_back(_pos);

	int count = 0;
	while (1) {
		bool filled = false;
		
		for (sf::Vector2u coord : posToFill) {
			if (this->getPixel(coord) == UNCLAIMED) {
				count++;
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

	count = (int)(pow(count * .9f, 1.25f) * .1f);
	if ((_clr & CLR_MASK) == RED) count *= 2;
	this->score->addScore(count);
}

sf::Vector2u GameField::getQixPos(int _id) {
	int i = 0;
	for (std::list<Qix*>::iterator q = this->qixList.begin(); q != this->qixList.end(); ++q) {
		if (i == _id) return (*q)->getPos();
		i++;
	}
}