#pragma once
#include <vector>

#include "toolbox/toolbox.hpp"
#include "Window.hpp"

class BouncingBox {
private:
	enum ColorState {
		CLR_RED = 0,
		CLR_YEL,
		CLR_GRN,
		CLR_CYN,
		CLR_BLU,
		CLR_MGT,
		CLR_TOTAL /// For modulo computing, leave at the end
	};

	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Vector2f size;
	enum ColorState clr;
	int id;

	static sf::RectangleShape rectRender;
	static std::vector<BouncingBox> list;

	void nextColor();
	sf::Color getColor();

public:
	BouncingBox(sf::Vector2f _pos, sf::Vector2f _size);
	BouncingBox(sf::Vector2f _pos, sf::Vector2f _vel, sf::Vector2f _size);

	static void create(BouncingBox _box);
	static void clearList();
	static void updateAll(Window& _w);
	static void renderAll(Window& _w);

	void move(Window& _w);
	void render(Window& _w);
};

