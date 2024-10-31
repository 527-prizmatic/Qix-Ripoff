#include "Game.hpp"
#include "../Core.hpp"
#include "../BouncingBox.hpp"

namespace states {
	Game::Game(Core* _core) {
		this->core = _core;
	}

	void Game::init() {
		for (int i = 0; i < 100; i++) {
			BouncingBox::create(BouncingBox(sf::Vector2f(rand() % 600 + 50.f, rand() % 400 + 50.f), vect::normalize(sf::Vector2f(rand() % 201 - 100.f, rand() % 201 - 100.f)) * 100.f, sf::Vector2f(10.f, 10.f)));
		}
	}

	void Game::update() {
		BouncingBox::updateAll(this->core->getWindow());
		if (this->core->getKeyboard().pressed("OpenMenu") || this->core->getMouse().clicked(sf::Mouse::Left)) this->core->requestStateChange(GameState::MENU);
		if (this->core->getMouse().clicked(sf::Mouse::Right)) this->core->getKeyboard().setKey("OpenMenu", sf::Keyboard::Key::R);
	}

	void Game::render() {
		BouncingBox::renderAll(this->core->getWindow());
	}

	void Game::unload() {
		BouncingBox::clearList();
	}
}