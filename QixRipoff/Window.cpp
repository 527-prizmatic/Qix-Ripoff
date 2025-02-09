#include "Window.hpp"

sf::Sprite Window::renderSpr;
sf::Shader* Window::shaderCrt;

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

void Window::preinit() {
	Window::shaderCrt = new sf::Shader();
	if (Window::shaderCrt != nullptr) {
		Window::shaderCrt->loadFromFile("..\\assets\\shaders\\crt.frag", sf::Shader::Type::Fragment);
	}
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
	static float shdTimer = 0.f;
	shdTimer += tutil::getDelta();

	Window::renderSpr.setTexture(this->rTex->getTexture());



	if (Window::shaderCrt) {
		Window::shaderCrt->setUniform("texture", this->rTex->getTexture());
		Window::shaderCrt->setUniform("uRes", this->currentView.value()->getView().getSize());
		Window::shaderCrt->setUniform("uTime", shdTimer);
		sf::Vector2f v = sf::Vector2f(this->currentView.value()->getView().getSize().x / (float)this->size.x, this->currentView.value()->getView().getSize().y / (float)this->size.y);
		Window::shaderCrt->setUniform("uZoom", v);
		Window::renderSpr.setTexture(this->rTex->getTexture());
	}
	else {
		/// The screen flip directly comes integrated into the shader, but it never hurts to still have it just in case the shader fails
		Window::renderSpr.setPosition(sf::Vector2f(0.f, (float)this->rTex->getSize().y));
		Window::renderSpr.setScale(1.f, -1.f);
	}
	
	this->window->draw(Window::renderSpr, sf::RenderStates(Window::shaderCrt));
	this->window->display();
}

void Window::update() {
	this->size = this->window.get()->getSize();
	this->aspectRatio = (float)this->size.x / (float)this->size.y;

	if (this->currentView.has_value()) {
		this->window->setView(this->currentView.value()->getView());
	}
	else {
		this->window->setView(this->window.get()->getDefaultView());
	}

	while (this->window->pollEvent(this->evt)) {
		if (this->evt.type == sf::Event::Closed)
			this->window->close();

		if (this->evt.type == sf::Event::KeyPressed) {
			if (this->evt.key.code == sf::Keyboard::Key::F11) {
				this->toggleFullscreen();
			}
		}
	}
}

void Window::draw(sf::Drawable& _obj) {
	this->rTex->draw(_obj);
}

sf::Vector2f Window::forceAspectRatio(sf::Vector2f _input, float _ratio) {
	float ratioOff = this->aspectRatio / _ratio;
	if (ratioOff > 1.f) {
		_input.x *= ratioOff;
	}
	else {
		_input.y *= ratioOff;
	}
	return _input;
}

void Window::toggleFullscreen()
{
	this->window->close();
	this->fullscreen = !this->fullscreen;
	this->setup();
}
