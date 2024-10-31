#include "Menu.hpp"
#include "../Core.hpp"

sf::Sprite sprite;
sf::Texture texture;
sf::Font font;
sf::Text text;

namespace states {
	Menu::Menu(Core* _core) {
		this->core = _core;
	}

	void Menu::init() {
		font.loadFromFile("../assets/fonts/qix-small.ttf");
		text.setFont(font);
		text.setString("Press Enter to start");
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		text.setPosition(100, 100);

		texture.loadFromFile("../assets/Textures/bgMenu.png");
		sprite.setTexture(texture);
		sprite.setScale(1.f, 1.f);
		sprite.setPosition(0, 0);
	}

	void Menu::update() {
		if (this->core->getKeyboard().pressed("OpenGame") || this->core->getMouse().clicked(sf::Mouse::Left)) this->core->requestStateChange(GameState::GAME);
	}

	void Menu::render() {
		this->core->getWindow().draw(sprite);
		this->core->getWindow().draw(text);
	}

	void Menu::unload() {
	}
}