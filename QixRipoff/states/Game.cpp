#include "Game.hpp"
#include "../Core.hpp"
#include "../resources/Textures.hpp"

namespace states {
	Game::Game(Core* _core) {
		this->core = _core;
	}

	void Game::init() {
		this->field = GameField(this->core, sf::Vector2u(128U, 128U));
		this->field.setPixel(sf::Vector2u(2, 2), FieldPixelState::CLAIMED_RED);
		this->player = Player(this->core, &this->field, sf::Vector2u(0, 0), 3);

		Texture::preload("../assets/textures/marker.png", "marker");
	}

	void Game::update() {
		if (this->core->getMouse().held(sf::Mouse::Middle)) {
			this->field.setPixel(sf::Vector2u(rand() % 128, rand() % 128), FieldPixelState::CLAIMED_BLUE);
			this->field.generateTexture();
		}

		this->field.update();
		this->player.update();

		if (this->core->getKeyboard().pressed("OpenMenu") || this->core->getMouse().clicked(sf::Mouse::Left)) this->core->requestStateChange(GameState::MENU);
	}

	void Game::render() {
		this->field.render(this->core->getWindow());
		this->player.draw();
	}

	void Game::unload() {

	}
}