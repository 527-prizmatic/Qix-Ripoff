#include "Mouse.hpp"
#include "../Window.hpp"

namespace ctrl {
	Mouse::Mouse() {
		this->window = nullptr;
		for (int btn = 0; btn < Mouse::btnCount; btn++) {
			this->state[btn] = IDLE;
		}
	}

	Mouse::Mouse(class Window* _window) {
		this->window = _window;
		for (int btn = 0; btn < Mouse::btnCount; btn++) {
			this->state[btn] = IDLE;
		}
	}

	void Mouse::update() {
		for (int btn = 0; btn < Mouse::btnCount; btn++) {
			bool clicked = false;
			if (this->window->hasFocus()) {
				clicked = sf::Mouse::isButtonPressed((sf::Mouse::Button)btn);
			}

			if (clicked) {
				if (this->state[btn] == IDLE) this->state[btn] = CLICK;
				else this->state[btn] = HOLD;
			}
			else {
				if (this->state[btn] == HOLD) this->state[btn] = RELEASE;
				else this->state[btn] = IDLE;
			}
		}
	}

	bool Mouse::idle(sf::Mouse::Button _btn) {
		return this->state[_btn] == RELEASE || this->state[_btn] == IDLE;
	}

	bool Mouse::clicked(sf::Mouse::Button _btn) {
		return this->state[_btn] == CLICK;
	}

	bool Mouse::held(sf::Mouse::Button _btn) {
		return this->state[_btn] == CLICK || this->state[_btn] == HOLD;
	}

	bool Mouse::released(sf::Mouse::Button _btn) {
		return this->state[_btn] == RELEASE;
	}
}