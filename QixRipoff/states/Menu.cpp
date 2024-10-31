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

		texture.loadFromFile("../assets/Textures/bgMenu.png");
		sprite.setTexture(texture);
	}

	void Menu::update() {
		if (this->core->getKeyboard().pressed("OpenGame") || this->core->getMouse().clicked(sf::Mouse::Left)) this->core->requestStateChange(GameState::GAME);
	}

	void Menu::render() {
		sprite.setScale(1.f, 1.f);
		sprite.setPosition(0, 0);
		this->core->getWindow().draw(sprite);

		text.setString("Play");
		text.setCharacterSize(5);
		text.setFillColor(sf::Color::White);
		text.setPosition(100, 100);
		this->core->getWindow().draw(text);

		text.setString("Options");
		text.setCharacterSize(5);
		text.setFillColor(sf::Color::White);
		text.setPosition(100, 130);
		this->core->getWindow().draw(text);

		text.setString("Hight socre");
		text.setCharacterSize(5);
		text.setFillColor(sf::Color::White);
		text.setPosition(100, 160);
		this->core->getWindow().draw(text);
	}

	void Menu::unload() {
	}
}