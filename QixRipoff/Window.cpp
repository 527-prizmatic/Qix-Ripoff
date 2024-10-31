#include "Window.hpp"

sf::Sprite Window::renderSpr;

Window::Window() {
	this->size = sf::Vector2u(800U, 600U);
	this->title = "Window";
	this->fullscreen = false;

	this->setup();
}

Window::Window(sf::Vector2u _size, std::string _title, bool _fullscreen) {
	this->size = _size;
	this->title = _title;
	this->fullscreen = _fullscreen;

	this->setup();
}

Window::Window(unsigned int _width, unsigned int _height, std::string _title, bool _fullscreen) {
	this->size = sf::Vector2u(_width, _height);
	this->title = _title;
	this->fullscreen = _fullscreen;

	this->setup();
}

void Window::setup() {
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(this->size.x, this->size.y), this->title, this->fullscreen ? 8U : 7U);
	this->window->setFramerateLimit(60);

	this->rTex = std::make_unique<sf::RenderTexture>();
	this->rTex->create(this->size.x, this->size.y);
}

void Window::beginRendering() {
	this->window->clear();
	this->rTex->clear();
}

void Window::endRendering() {
	Window::renderSpr.setTexture(this->rTex->getTexture());
	Window::renderSpr.setPosition(sf::Vector2f());
	Window::renderSpr.setScale(1.f, 1.f);
	this->window->draw(Window::renderSpr);
	this->window->display();
}

void Window::update() {
	while (this->window->pollEvent(this->evt)) {
		if (this->evt.type == sf::Event::Closed)
			this->window->close();

		if (this->evt.type == sf::Event::KeyPressed) {
			if (this->evt.key.code == sf::Keyboard::Key::F11) {
				this->window->close();
				this->fullscreen = !this->fullscreen;
				this->setup();
			}
		}
	}
}

void Window::draw(sf::Drawable& _obj) {
	this->rTex->draw(_obj);
}

/*
sf::RenderWindow* Window::operator->() const noexcept {
	return this->window.get();
}
*/