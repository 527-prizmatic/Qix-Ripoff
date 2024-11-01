#include "Game.hpp"
#include "../Core.hpp"

namespace states {
	Game::Game(Core* _core) {
		this->core = _core;
	}

	void Game::init() {
		this->field = GameField(sf::Vector2u(128U, 128U));
		this->field.setPixel(sf::Vector2u(2, 2), FieldPixelState::CLAIMED_RED);
	}

	void Game::update() {
		if (this->core->getMouse().held(sf::Mouse::Middle)) {
			this->field.setPixel(sf::Vector2u(rand() % 128, rand() % 128), FieldPixelState::CLAIMED_BLUE);
			this->field.generateTexture();
		}

//		if (this->core->getKeyboard().pressed("OpenMenu") || this->core->getMouse().clicked(sf::Mouse::Left)) this->core->requestStateChange(GameState::MENU);
//		if (this->core->getMouse().clicked(sf::Mouse::Right)) this->core->getKeyboard().setKey("OpenMenu", sf::Keyboard::Key::R);
	}

	void Game::render() {
		this->field.render(this->core->getWindow());
	}

	void Game::unload() {

	}
}