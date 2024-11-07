#include "Preinit.hpp"
#include "Core.hpp"

#include "states/Menu.hpp"
#include "states/Game.hpp"

#include "resources/Textures.hpp"

#include "Score.hpp"

const std::string KeyOpenMenu = "OpenMenu";
const std::string KeyOpenGame = "OpenGame";
const std::string KeyUp = "Up";
const std::string KeyDown = "Down";
const std::string KeyLeft = "Left";
const std::string KeyRight = "Right";
const std::string KeyOK = "OK";
const std::string KeyKaboom = "Kaboom";


const std::string controllerUp = "Up";
const std::string controllerDown = "Down";
const std::string controllerLeft = "Left";
const std::string controllerRight = "Right";
const std::string controllerOK = "OK";
const std::string controllerKaboom = "Kaboom";


void preinit(Core& _core) {
	std::srand(std::time(NULL));
	Texture::preinit();
	Score::preinit();
	_core.registerState(MENU, (states::State*)(new states::Menu(&_core)));
	_core.registerState(GAME, (states::State*)(new states::Game(&_core)));
}

void registerControls(Core& _core) {
//	_core.getKeyboard().addKey(KeyOpenMenu, sf::Keyboard::Key::B);
//	_core.getKeyboard().addKey(KeyOpenGame, sf::Keyboard::Key::A);
	_core.getKeyboard().addKey(KeyUp, sf::Keyboard::Key::Up);
	_core.getKeyboard().addKey(KeyDown, sf::Keyboard::Key::Down);
	_core.getKeyboard().addKey(KeyLeft, sf::Keyboard::Key::Left);
	_core.getKeyboard().addKey(KeyRight, sf::Keyboard::Key::Right);
	_core.getKeyboard().addKey(KeyOK, sf::Keyboard::Key::A);
	_core.getKeyboard().addKey(KeyKaboom, sf::Keyboard::Key::E);

	_core.getController().addKey(controllerUp, DPAD_UP);
	_core.getController().addKey(controllerDown, DPAD_DOWN);
	_core.getController().addKey(controllerLeft, DPAD_LEFT);
	_core.getController().addKey(controllerRight, DPAD_RIGHT);
	_core.getController().addKey(controllerOK, A);
	_core.getController().addKey(controllerKaboom, B);
}