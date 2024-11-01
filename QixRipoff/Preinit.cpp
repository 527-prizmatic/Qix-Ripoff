#include "Preinit.hpp"
#include "Core.hpp"

#include "states/Menu.hpp"
#include "states/Game.hpp"

const std::string KeyOpenMenu = "OpenMenu";
const std::string KeyOpenGame = "OpenGame";
const std::string KeyUp = "Up";
const std::string KeyDown = "Down";
const std::string KeyLeft = "Left";
const std::string KeyRight = "Right";
const std::string KeyOK = "OK";
const std::string KeyKaboom = "Kaboom";



void preinit(Core& _core) {
	_core.registerState(MENU, (states::State*)(new states::Menu(&_core)));
	_core.registerState(GAME, (states::State*)(new states::Game(&_core)));
}

void registerControls(Core& _core) {
	_core.getKeyboard().addKey(KeyOpenMenu, sf::Keyboard::Key::B);
	_core.getKeyboard().addKey(KeyOpenGame, sf::Keyboard::Key::A);
	_core.getKeyboard().addKey(KeyUp, sf::Keyboard::Key::Up);
	_core.getKeyboard().addKey(KeyDown, sf::Keyboard::Key::Down);
	_core.getKeyboard().addKey(KeyLeft, sf::Keyboard::Key::Left);
	_core.getKeyboard().addKey(KeyRight, sf::Keyboard::Key::Right);
	_core.getKeyboard().addKey(KeyOK, sf::Keyboard::Key::Enter);
	_core.getKeyboard().addKey(KeyKaboom, sf::Keyboard::Key::Escape);
}