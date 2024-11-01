#include "Preinit.hpp"
#include "Core.hpp"

#include "states/Menu.hpp"
#include "states/Game.hpp"

const std::string KeyOpenMenu = "OpenMenu";
const std::string KeyOpenGame = "OpenGame";
const std::string KeySwitchSelectMenuUp = "ChoiseMenuUp";
const std::string KeySwitchSelectMenuDown = "ChoiseMenuDown";
const std::string KeySelectMenu = "SelectMenu";


void preinit(Core& _core) {
	_core.registerState(MENU, (states::State*)(new states::Menu(&_core)));
	_core.registerState(GAME, (states::State*)(new states::Game(&_core)));
}

void registerControls(Core& _core) {
	_core.getKeyboard().addKey(KeyOpenMenu, sf::Keyboard::Key::B);
	_core.getKeyboard().addKey(KeyOpenGame, sf::Keyboard::Key::A);
	_core.getKeyboard().addKey(KeySwitchSelectMenuUp, sf::Keyboard::Key::Up);
	_core.getKeyboard().addKey(KeySwitchSelectMenuDown, sf::Keyboard::Key::Down);
	_core.getKeyboard().addKey(KeySelectMenu, sf::Keyboard::Key::Enter);
}