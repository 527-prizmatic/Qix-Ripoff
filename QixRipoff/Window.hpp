#pragma once
#include "toolbox/toolbox.hpp"
#include "View.hpp"

class Window {
private:
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<sf::RenderTexture> rTex;
	std::optional<View*> currentView;
	
	std::string title;
	bool fullscreen;
	sf::Vector2u size;
	sf::Event evt;
	float aspectRatio;

	static sf::Sprite renderSpr;
	static sf::Shader* shaderCrt;
	void setup();

public:
	Window();
	Window(sf::Vector2u _size, std::string _title, bool _fullscreen);
	Window(unsigned int _width, unsigned int _height, std::string _title, bool _fullscreen);

	static void preinit();

	void beginRendering();
	void endRendering();
	void update();

	void draw(sf::Drawable& _obj);

	bool isOpen() { return this->window->isOpen(); }
	bool hasFocus() { return this->window->hasFocus(); }
	sf::Vector2u getSize() { return this->size; }

	sf::Vector2f forceAspectRatio(sf::Vector2f _input, float _ratio);

	inline void setView(View* _v) { this->currentView = _v; }
	inline View* getView() { return this->currentView.value(); }
	inline void resetView() { this->currentView.reset(); }

	sf::Event getEvent() { return this->evt; }

	void toggleFullscreen();
};
