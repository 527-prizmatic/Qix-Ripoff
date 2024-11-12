	#include "Game.hpp"
#include "../Core.hpp"
#include "../resources/Textures.hpp"

const float difficulty = 0.75f;

float timerMultiMemory = 1.f;
int lifeMemory = 3;

bool isPaused = false;

sf::RectangleShape Paused;

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
		if (!isPaused)
		{
			static float endLevelTimer = 0.f;
			if (this->field.getFillRatio() >= difficulty) {
				endLevelTimer += tutil::getDelta();
				if (endLevelTimer >= 2.f) {
					this->score.addScore((int)(100000 * (this->field.getFillRatio() - difficulty)));
					this->field = GameField(this->core, sf::Vector2u(161U, 161U), &this->score);
					timerMultiMemory = this->player.getTimerMultiplier() + 0.1f;
					if (this->player.getLife() < 3) lifeMemory = this->player.getLife() + 1;
					else lifeMemory = this->player.getLife();
					this->player = Player(this->core, &this->field, sf::Vector2u(0U, 160U), lifeMemory);
					this->player.setTimerMultiplier(timerMultiMemory);
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

				if (this->core->getKeyboard().pressed(KeyOK)) this->core->requestStateChange(GameState::MENU);
			}
			if (this->core->getKeyboard().pressed(KeyPaused)) togglePause();
		}
		else
		{
			if (this->core->getKeyboard().pressed(KeyPaused)) togglePause();
		}
	}

	void Game::render() {
		this->field.render(this->core->getWindow());
		this->player.draw();
		this->renderHUD();
		if (isPaused)
		{
			Paused.setSize(sf::Vector2f(this->core->getWindow().getSize()));
			Paused.setFillColor(sf::Color(0, 0, 0, 128));
			Paused.setPosition(0.f, 0.f);
			this->core->getWindow().draw(Paused);
			this->txtDisplay.setString("PAUSED");
			this->txtDisplay.setPosition(sf::Vector2f(100.f, 100.f));
			this->core->getWindow().draw(this->txtDisplay);
		}
	}

	void Game::unload() {

	}

	void Game::renderHUD() {
		this->score.render(this->core->getWindow(), sf::Vector2u(48U, 18U));
		this->txtDisplay.setString("LV" + std::to_string(this->level) + " " + std::to_string((int)(this->field.getFillRatio() * 100)) + " OF " + std::to_string((int)(difficulty * 100)));
		this->txtDisplay.setPosition(sf::Vector2f(70.f, 18.f));
		this->core->getWindow().draw(this->txtDisplay);
		this->txtDisplay.setString("LIFE " + std::to_string(this->player.getLife()));
		this->txtDisplay.setPosition(sf::Vector2f(170.f, 18.f));
		this->core->getWindow().draw(this->txtDisplay);
		this->txtDisplay.setString("MOVE BOOST " + std::to_string((float)(this->player.getTimerMultiplier())));
		this->txtDisplay.setPosition(sf::Vector2f(55.f, 200.f));
		this->core->getWindow().draw(this->txtDisplay);
	}
	void Game::togglePause()
	{
		isPaused = !isPaused;
	}
}