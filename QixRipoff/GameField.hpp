#pragma once
#include "toolbox/toolbox.hpp"
#include "Window.hpp"
//#include "Sparks.hpp"
#include "Core.hpp"
//#include "Qix.hpp"

class Score;

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
	int pixelCount;
	int pixelsClaimed;
	Score* score;
	float timerSparkSpawn;
	std::list<class Qix*> qixList;
	std::list<class Sparks*> sparksList;
public:
	enum SearchDir {
		HORIZONTAL,
		VERTICAL
	};

	GameField();
	GameField(Core* _core, sf::Vector2u _size, Score* _score);

	void update(Core* _core, class Player* _plr);
	void createOutline();
	void generateTexture();
	void render(Window& _window);
	FieldPixelState getPixel(sf::Vector2u _pos);
	void setPixel(sf::Vector2u _pos, FieldPixelState _state);
	bool replaceAll(FieldPixelState _state_old, FieldPixelState _state_new);
	inline const sf::Vector2u getSize() { return this->size; }
	inline const sf::Vector2u getRenderOffset() { return this->renderOffset; }
	bool isValidMovement(sf::Vector2u _pos);

	int countPathCrossings(sf::Vector2u _src, sf::Vector2u _dest, enum SearchDir _dir);
	void iterativeFill(sf::Vector2u _pos, FieldPixelState _clr);
	float getFillRatio() const { return (float)this->pixelsClaimed / (float)this->pixelCount;  }

	sf::Vector2u getQixPos(int _id);
};