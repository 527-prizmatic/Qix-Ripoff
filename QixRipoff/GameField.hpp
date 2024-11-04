#pragma once
#include "toolbox/toolbox.hpp"
#include "Window.hpp"
#include "Core.hpp"
//#include "Qix.hpp"

typedef enum {
	UNCLAIMED,
	STIX,
	CLAIMED,
	EDGE,
	TYPE_MASK = 0b111111,

	BLUE = 1 << 6,
	RED = 1 << 7,
	CLR_MASK = 0b11000000,

	STIX_BLUE = STIX | BLUE,
	STIX_RED = STIX | RED,
	CLAIMED_BLUE = CLAIMED | BLUE,
	CLAIMED_RED = CLAIMED | RED
} FieldPixelState;

class GameField {
private:
	sf::Vector2u size;
	sf::Vector2u renderOffset;
	sf::Image img;
	sf::Texture tex;
	sf::Sprite spr;
	/// Add some enemies in there
//	std::list<class Qix*> qixList;

public:
	GameField();
	GameField(Core* _core, sf::Vector2u _size);

	void update();
	void createOutline();
	void generateTexture();
	void render(Window& _window);
	FieldPixelState getPixel(sf::Vector2u _pos);
	void setPixel(sf::Vector2u _pos, FieldPixelState _state);
	inline const sf::Vector2u getSize() { return this->size; }
	inline const sf::Vector2u getRenderOffset() { return this->renderOffset; }
	bool isValidMovement(sf::Vector2u _pos);
};