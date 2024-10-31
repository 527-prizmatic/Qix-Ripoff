#pragma once
#include "../toolbox/toolbox.hpp"
#include "State.hpp"

namespace states {
	class Menu : public State {
	private:
		Core* core;
	public:
		Menu(Core* _core);
		void init();
		void update();
		void render();
		void unload();

		void treatPinkPixelTexture(sf::Texture& texture);
	};
}