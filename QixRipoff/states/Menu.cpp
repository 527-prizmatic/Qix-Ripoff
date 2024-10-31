#include "Menu.hpp"
#include "../Core.hpp"

namespace states {
	Menu::Menu(Core* _core) {
		this->core = _core;
	}

	void Menu::init() {
	}

	void Menu::update() {
		if (this->core->getKeyboard().pressed("OpenGame") || this->core->getMouse().clicked(sf::Mouse::Left)) this->core->requestStateChange(GameState::GAME);
	}

	void Menu::render() {
	}

	void Menu::unload() {
	}
}