#include "Keyboard.hpp"
#include "../Window.hpp"

namespace ctrl {
	KeyEntry::KeyEntry(std::string _str, sf::Keyboard::Key _key) {
		this->id = _str;
		this->key = _key;
		this->state = IDLE;
	}

	Keyboard::Keyboard() {
		this->window = nullptr;
	}

	Keyboard::Keyboard(class Window* _window) {
		this->window = _window;
	}

	Keyboard& Keyboard::addKey(std::string _str, sf::Keyboard::Key _key) {
		this->keyReg.push_back(KeyEntry(_str, _key));
		return *this;
	}

	Keyboard& Keyboard::setKey(std::string _str, sf::Keyboard::Key _key) {
		for (KeyEntry& k : this->keyReg) {
			if (!k.getId().compare(_str)) {
				k.setKey(_key);
				return *this;
			}
		}
		return *this;
	}

	void Keyboard::update() {
		for (KeyEntry& k : this->keyReg) {
			bool clicked = false;
			if (this->window->hasFocus()) {
				clicked = sf::Keyboard::isKeyPressed(k.getKey());
			}

			if (clicked) {
				if (k.getState() == IDLE) k.setState(CLICK);
				else k.setState(HOLD);
			}
			else {
				if (k.getState() == HOLD) k.setState(RELEASE);
				else k.setState(IDLE);
			}
		}
	}

	bool Keyboard::idle(std::string _str) {
		for (KeyEntry& k : this->keyReg) {
			if (!k.getId().compare(_str)) {
				return k.getState() == RELEASE || k.getState() == IDLE;
			}
		}
		return false;
	}

	bool Keyboard::pressed(std::string _str) {
		for (KeyEntry& k : this->keyReg) {
			if (!k.getId().compare(_str)) {
				return k.getState() == CLICK;
			}
		}
		return false;
	}

	bool Keyboard::held(std::string _str) {
		for (KeyEntry& k : this->keyReg) {
			if (!k.getId().compare(_str)) {
				return k.getState() == CLICK || k.getState() == HOLD;
			}
		}
		return false;
	}

	bool Keyboard::released(std::string _str) {
		for (KeyEntry& k : this->keyReg) {
			if (!k.getId().compare(_str)) {
				return k.getState() == RELEASE;
			}
		}
		return false;
	}

}