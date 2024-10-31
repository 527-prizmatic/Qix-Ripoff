#pragma once
#include <string>
#include "toolbox/toolbox.hpp"

class Window {
private:
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<sf::RenderTexture> rTex;
	std::string title;
	bool fullscreen;
	sf::Vector2u size;
	sf::Event evt;

	static sf::Sprite renderSpr;
	void setup();

public:
	Window();
	Window(sf::Vector2u _size, std::string _title, bool _fullscreen);
	Window(unsigned int _width, unsigned int _height, std::string _title, bool _fullscreen);

	void beginRendering();
	void endRendering();
	void update();

	void draw(sf::Drawable& _obj);

	bool isOpen() { return this->window->isOpen(); }
	bool hasFocus() { return this->window->hasFocus(); }
	sf::Vector2u getSize() { return this->size; }

	// Discarded that one, too error-prone
//	sf::RenderWindow* operator->() const noexcept;
};
