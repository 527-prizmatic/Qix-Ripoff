#include "Menu.hpp"
#include "../Core.hpp"
#include "../Score.hpp"

#include "../resources/Textures.hpp"

sf::Sprite sprite;
sf::Texture texture;
sf::Texture textTittleMenu;
sf::Font font;
sf::Text text;

sf::RectangleShape rectangle;

bool toggleOptions;
bool toggleHighscores;
bool toggleTitleScreens;

//timer = tutil::getDelta();

int choix;
int choixOption;

namespace states {
	Menu::Menu(Core* _core) {
		this->core = _core;
	}

	void Menu::init() {
		font.loadFromFile("../assets/fonts/qix-small.ttf");
		text.setFont(font);

		Texture::preload("../assets/Textures/bgMenu.png", "bgMenu");
		Texture::treatPinkPixels("bgMenu");

		textTittleMenu.loadFromFile("../assets/bgm/tittleScreen.png");

		toggleOptions = false;
		toggleHighscores = false;
		toggleTitleScreens = true;

		choix = 0;
		choixOption = 0;
	}

	void Menu::update() {
		if (!toggleOptions && !toggleHighscores && !toggleTitleScreens)
		{
			if (this->core->getKeyboard().pressed("Up") || this->core->getController().pressed("Up"))
			{
				choix--;
			}
			if (this->core->getKeyboard().pressed("Down") || this->core->getController().pressed("Down"))
			{
				choix++;
			}
			if (choix > 2) choix = 0;
			if (choix < 0) choix = 2;
			if (this->core->getKeyboard().pressed("OK") || this->core->getController().pressed("OK"))
			{
				switch (choix) {
				case 0:
					this->core->requestStateChange(GameState::GAME);
					break;
				case 1:
					toggleOption();
					break;
				case 2:
					toggleHighscore();
					break;
				default:
					break;
				}
			}
		}
		else if (toggleOptions)
		{
			if (this->core->getKeyboard().pressed("Up") || this->core->getController().pressed("Up"))
			{
				choixOption--;
			}
			if (this->core->getKeyboard().pressed("Down") || this->core->getController().pressed("Down"))
			{
				choixOption++;
			}
			if (choixOption > 3) choixOption = 0;
			if (choixOption < 0) choixOption = 3;
			if (this->core->getKeyboard().pressed("OK") || this->core->getController().pressed("OK"))
			{
				switch (choixOption) {
				case 0:
					this->core->getWindow().toggleFullscreen();
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					toggleOption();
					break;
				}
			}

		}
		else if (toggleHighscores)
		{
			if (this->core->getKeyboard().pressed("OK") || this->core->getController().pressed("OK"))
			{
				toggleHighscore();
			}
		}
		else if (toggleTitleScreens)
		{
			if (this->core->getKeyboard().pressed("OK") || this->core->getController().pressed("OK"))
			{
				toggleTitleScreen();
			}
		}
		if (this->core->getKeyboard().pressed("Kaboom") || this->core->getController().pressed("Kaboom"))
		{
			exit(EXIT_SUCCESS);
		}
	}

	void Menu::render() {
		if (!toggleTitleScreens)
		{
			sprite.setScale(1.f, 1.f);
			sprite.setPosition(0, 0);
			sprite.setTexture(Texture::getTexture("bgMenu"));
			this->core->getWindow().draw(sprite);
			if (toggleOptions) {
				rectangle.setSize(sf::Vector2f(100, 100));
				rectangle.setFillColor(sf::Color::Red);
				rectangle.setPosition(100, 100);
				this->core->getWindow().draw(rectangle);
			}
			else if (toggleHighscores) {
				for (int i = 0; i < Score::highscores.size(); i++) {
					std::string str = std::to_string(Score::highscores[i].score);
					str.insert(str.begin(), 12 - str.size(), ' ');
					text.setString(Score::highscores[i].name + str);
					text.setCharacterSize(12);
					text.setFillColor(choix == 0 ? sf::Color::Red : sf::Color::White);
					text.setPosition(128.f, 100.f + i * 16.f);
					text.setOrigin(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height) * .5f);
					this->core->getWindow().draw(text);
				}
			}
			else {
				text.setString("Play");
				text.setCharacterSize(12);
				text.setFillColor(choix == 0 ? sf::Color::Red : sf::Color::White);
				text.setPosition(128, 104);
				text.setOrigin(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height) * .5f);
				this->core->getWindow().draw(text);

				text.setString("Options");
				text.setCharacterSize(12);
				text.setFillColor(choix == 1 ? sf::Color::Red : sf::Color::White);
				text.setPosition(128, 134);
				text.setOrigin(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height) * .5f);
				this->core->getWindow().draw(text);

				text.setString("High scores");
				text.setCharacterSize(12);
				text.setFillColor(choix == 2 ? sf::Color::Red : sf::Color::White);
				text.setPosition(128, 164);
				text.setOrigin(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height) * .5f);
				this->core->getWindow().draw(text);
			}
		}
		else if (toggleTitleScreens)
		{
			sprite.setScale(1.f, 1.f);
			sprite.setPosition(0, 0);
			sprite.setTexture(textTittleMenu);
			this->core->getWindow().draw(sprite);
		}
	}

	void Menu::unload() {
	}
	void Menu::toggleOption()
	{
		toggleOptions = !toggleOptions;
	}
	void Menu::toggleHighscore()
	{
		toggleHighscores = !toggleHighscores;
	}
	void Menu::toggleTitleScreen()
	{
		toggleTitleScreens = !toggleTitleScreens;
	}
}