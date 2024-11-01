#pragma once
#include "toolbox/toolbox.hpp"
#include "Window.hpp"

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
	sf::Image img;
	sf::Texture tex;
	sf::Sprite spr;
	/// Add some enemies in there

public:
	GameField();
	GameField(sf::Vector2u _size);

	void generateTexture();
	void render(Window& _window);
	FieldPixelState getPixel(sf::Vector2u _pos);
	void setPixel(sf::Vector2u _pos, FieldPixelState _state);
};