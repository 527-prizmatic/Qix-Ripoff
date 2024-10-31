#pragma once
#include "toolbox/toolbox.hpp"

class Window;

class View {
private:
	sf::View view;
	sf::Vector2f center;
	sf::Vector2f size;

public:
	View();
	View(Window& _w);
	View(sf::Vector2f _size);
	View(sf::Vector2f _tl, sf::Vector2f _br);

	const void setSize(sf::Vector2f _size);
	const void setCenter(sf::Vector2f _center);
	const void setCorners(sf::Vector2f _tl, sf::Vector2f _br);

	const sf::View& getView() { return this->view; }
};

