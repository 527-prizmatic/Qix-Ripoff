#include "Menu.hpp"
#include "../Core.hpp"

sf::Sprite sprite;
sf::Texture texture;
sf::Font font;
sf::Text text;

sf::RectangleShape rectangle;

bool toggleOptions;
bool toggleHighscores;

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

		texture.loadFromFile("../assets/Textures/bgMenu.png");
		treatPinkPixelTexture(texture);
		sprite.setTexture(texture);


		toggleOptions = false;
		toggleHighscores = false;

		choix = 0;
		choixOption = 0;
	}

	void Menu::update() {
		if (!toggleOptions && !toggleHighscores)
		{
			if (this->core->getKeyboard().pressed("Up"))
			{
				choix--;
			}
			if (this->core->getKeyboard().pressed("Down"))
			{
				choix++;
			}
			if (choix > 2) choix = 0;
			if (choix < 0) choix = 2;
			if (this->core->getKeyboard().pressed("OK"))
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
			if (this->core->getKeyboard().pressed("Kaboom"))
			{
				exit(EXIT_SUCCESS);
			}
		}
		else if (toggleOptions)
		{
			if (this->core->getKeyboard().pressed("Up"))
			{
				choixOption--;
			}
			if (this->core->getKeyboard().pressed("Down"))
			{
				choixOption++;
			}
			if (choixOption > 3) choixOption = 0;
			if (choixOption < 0) choixOption = 3;
			if (this->core->getKeyboard().pressed("OK"))
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
			if (this->core->getKeyboard().pressed("OK"))
			{
				toggleHighscore();
			}
		}
	}

	void Menu::render() {
		sprite.setScale(1.f, 1.f);
		sprite.setPosition(0, 0);
		this->core->getWindow().draw(sprite);

		text.setString("Play");
		text.setCharacterSize(10);
		text.setFillColor(choix == 0 ? sf::Color::Red : sf::Color::White);
		text.setPosition(100, 100);
		this->core->getWindow().draw(text);

		text.setString("Options");
		text.setCharacterSize(10);
		text.setFillColor(choix == 1 ? sf::Color::Red : sf::Color::White);
		text.setPosition(100, 130);
		this->core->getWindow().draw(text);

		text.setString("Hight socre");
		text.setCharacterSize(10);
		text.setFillColor(choix == 2 ? sf::Color::Red : sf::Color::White);
		text.setPosition(100, 160);
		this->core->getWindow().draw(text);

		if (toggleOptions) {
			rectangle.setSize(sf::Vector2f(100, 100));
			rectangle.setFillColor(sf::Color::Red);
			rectangle.setPosition(100, 100);
			this->core->getWindow().draw(rectangle);
		}
		else if (toggleHighscores) {
			rectangle.setSize(sf::Vector2f(100, 100));
			rectangle.setFillColor(sf::Color::Green);
			rectangle.setPosition(100, 130);
			this->core->getWindow().draw(rectangle);
		}
	}

	void Menu::unload() {
	}
	void Menu::treatPinkPixelTexture(sf::Texture& texture)
	{
		sf::Image image = texture.copyToImage();
		for (int x = 0; x < image.getSize().x; x++)
		{
			for (int y = 0; y < image.getSize().y; y++)
			{
				if (image.getPixel(x, y) == sf::Color(171, 0, 66) || image.getPixel(x, y) == sf::Color(255, 0, 182))
				{
					image.setPixel(x, y, sf::Color::Transparent);
				}
			}
		}
		texture.update(image);
	}
	void Menu::toggleOption()
	{
		toggleOptions = !toggleOptions;
	}
	void Menu::toggleHighscore()
	{
		toggleHighscores = !toggleHighscores;
	}
}