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
	CLAIMED_RED = CLAIMED | RED,

	DEBUG
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

	/// Generates the map's initial white outline.
	void createOutline();

	/// Turns the current bitmap into a renderable sf::Texture object.
	void generateTexture();

	/// Displays the most recently generated texture on-screen.
	void render(Window& _window);
	
	/// Looks up what kind of pixel is at the given coordinates.
	/// While normally not possible to look up, the outside of the map is counted as being a blue claimed area as a safety measure.
	FieldPixelState getPixel(sf::Vector2u _pos);

	/// Changes the pixel at the given location.
	void setPixel(sf::Vector2u _pos, FieldPixelState _state);

	/// Replaces all pixels of a given type with pixels of another type.
	bool replaceAll(FieldPixelState _state_old, FieldPixelState _state_new);
	inline const sf::Vector2u getSize() { return this->size; }
	inline const sf::Vector2u getRenderOffset() { return this->renderOffset; }

	/// Checks whether the given map pixel is surrounded by unclaimed areas. Used for calculating player and Sparx movement options.
	bool isValidMovement(sf::Vector2u _pos);

	/// Traces a taxicab path between two given points and counts the amount of times a white edge pixel is found along that path.
	/// Originally intended to be used for detecting on which side of a Stix the Qix was located, although this method is flawed and was eventually abandoned.
	[[deprecated("Non-functional. Use pathfindDetection() instead.")]] int countPathCrossings(sf::Vector2u _src, sf::Vector2u _dest, enum SearchDir _dir);

	/// Attempts to pathfind between the two given points, stopping at everything that isn't an unclaimed pixel.
	/// While particularly terrible in terms of performance (it uses a breadth-first algorithm), it is the most functional method we could find for detecting on which side of the Stix a Qix is located.
	/// Various optimizations were found, the most drastic of which consisting in eliminating paths that would ever stray too far away from the Qix, using a computational method loosely inspired from the A* algorithm.
	/// Note that this function does not actually find a path between the two points - it merely checks whether such a path exists.
	bool pathfindDetection(sf::Vector2u _src, sf::Vector2u _dest);

	/// Uses a pseudo-recursion system to fill an area of the map bounded by white edge pixels.
	/// This system repeatedly fills a list of pixels, then marks the adjacent ones for filling on the next pass.
	/// It was originally intended to be implemented using recursivity, but was turned into a simple loop due to memory issues.
	void iterativeFill(sf::Vector2u _pos, FieldPixelState _clr);
	float getFillRatio() const { return (float)this->pixelsClaimed / (float)this->pixelCount;  }

	/// Returns the position of the Qix with the given ID.
	sf::Vector2u getQixPos(int _id);
};