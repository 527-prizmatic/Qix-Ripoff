	#include "Game.hpp"
#include "../Core.hpp"
#include "../resources/Textures.hpp"

const float difficulty = 0.75f;

namespace states {
	sf::Text Game::txtDisplay;
	sf::Font Game::txtFont;

	Game::Game(Core* _core):score(_core->getScores()) {
		this->core = _core;
		this->level = 1;
	}

	void Game::init() {
		this->field = GameField(this->core, sf::Vector2u(161U, 161U), &this->score);
		this->player = Player(this->core, &this->field, sf::Vector2u(0U, 160U), 3);
		this->score = this->core->getScores();
		this->level = 1;

		Texture::preload("../assets/textures/marker.png", "marker");
		Game::txtFont.loadFromFile("../assets/fonts/qix-small.ttf");
		Game::txtDisplay.setFont(Game::txtFont);
		Game::txtDisplay.setCharacterSize(9);
	}

	void Game::update() {
		static float endLevelTimer = 0.f;
		if (this->field.getFillRatio() >= difficulty) {
			endLevelTimer += tutil::getDelta();
			if (endLevelTimer >= 2.f) {
				this->score.addScore((int)(100000 * (this->field.getFillRatio() - difficulty)));
				this->field = GameField(this->core, sf::Vector2u(161U, 161U), &this->score);
				this->player = Player(this->core, &this->field, sf::Vector2u(0U, 160U), 3);
				this->level++;
				this->field.update(this->core, &(this->player));
				this->player.update();
				endLevelTimer = 0.f;
			}
		}
		else {
			endLevelTimer = 0.f;
			this->field.update(this->core, &(this->player));
			this->player.update();

			if (this->core->getKeyboard().pressed("OpenMenu")) this->core->requestStateChange(GameState::MENU);
		}
	}

	void Game::render() {
		this->field.render(this->core->getWindow());
		this->player.draw();
		this->renderHUD();
	}

	void Game::unload() {

	}

	void Game::renderHUD() {
		this->score.render(this->core->getWindow(), sf::Vector2u(48U, 18U));
		this->txtDisplay.setString("LV" + std::to_string(this->level) + " " + std::to_string((int)(this->field.getFillRatio() * 100)) + " OF " + std::to_string((int)(difficulty * 100)));
		this->txtDisplay.setPosition(sf::Vector2f(100.f, 18.f));
		this->core->getWindow().draw(this->txtDisplay);
	}
}