	#include "Game.hpp"
#include "../Core.hpp"
#include "../resources/Textures.hpp"


namespace states {
	Game::Game(Core* _core) {
		this->core = _core;
	}

	void Game::init() {
		this->field = GameField(this->core, sf::Vector2u(128U, 128U));
		this->player = Player(this->core, &this->field, sf::Vector2u(0, 0), 3);

		Texture::preload("../assets/textures/marker.png", "marker");
	}

	void Game::update() {
		this->field.update(&(this->player));
		this->player.update();

		if (this->core->getKeyboard().pressed("OpenMenu")) this->core->requestStateChange(GameState::MENU);
	}

	void Game::render() {
		this->field.render(this->core->getWindow());
		this->player.draw();
	}

	void Game::unload() {

	}
}