#pragma once
#include "../toolbox/toolbox.hpp"
#include <vector>

class Window;

namespace ctrl {
	class KeyEntry {
	private:
		std::string id;
		sf::Keyboard::Key key;
		ButtonState state;

	public:
		KeyEntry(std::string _str, sf::Keyboard::Key _key);

		const std::string getId() { return this->id; }
		const sf::Keyboard::Key getKey() { return this->key; }
		const ButtonState getState() { return this->state; }

		void setKey(sf::Keyboard::Key _key) { this->key = _key; }
		void setState(ButtonState _state) { this->state = _state; }
	};

	class Keyboard {
	private:
		int keyCtrlCount;

		class Window* window;
		std::vector<KeyEntry> keyReg;
	public:
		Keyboard();
		Keyboard(Window* _window);
		void setWindow(Window* _window) { this->window = _window; }

		Keyboard& addKey(std::string _str, sf::Keyboard::Key _key);
		Keyboard& setKey(std::string _str, sf::Keyboard::Key _key);

		void update();

		bool idle(std::string _str);
		bool pressed(std::string _str);
		bool held(std::string _str);
		bool released(std::string _str);
	};
}