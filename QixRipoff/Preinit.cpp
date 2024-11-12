#include "Preinit.hpp"
#include "Core.hpp"

#include "states/Menu.hpp"
#include "states/Game.hpp"
#include "states/Leaderboard.hpp"

#include "resources/Textures.hpp"

#include "Score.hpp"




void preinit(Core& _core) {
	std::srand((unsigned int)std::time(NULL));
	Texture::preinit();
	Score::preinit();
	Window::preinit();
	_core.registerState(MENU, (states::State*)(new states::Menu(&_core)));
	_core.registerState(GAME, (states::State*)(new states::Game(&_core)));
	_core.registerState(LEADERBOARD, (states::State*)(new states::Leaderboard(&_core)));
}

void registerControls(Core& _core) {
	_core.getKeyboard().addKey(KeyUp, sf::Keyboard::Key::Up);
	_core.getKeyboard().addKey(KeyDown, sf::Keyboard::Key::Down);
	_core.getKeyboard().addKey(KeyLeft, sf::Keyboard::Key::Left);
	_core.getKeyboard().addKey(KeyRight, sf::Keyboard::Key::Right);
	_core.getKeyboard().addKey(KeyOK, sf::Keyboard::Key::A);
	_core.getKeyboard().addKey(KeyKaboom, sf::Keyboard::Key::E);
	_core.getKeyboard().addKey(KeyPaused, sf::Keyboard::Key::Enter);

	_core.getController().addKey(KeyUp, DPAD_UP);
	_core.getController().addKey(KeyDown, DPAD_DOWN);
	_core.getController().addKey(KeyLeft, DPAD_LEFT);
	_core.getController().addKey(KeyRight, DPAD_RIGHT);
	_core.getController().addKey(KeyOK, A);
	_core.getController().addKey(KeyKaboom, B);
}