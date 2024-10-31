#pragma once
#include "../toolbox/toolbox.hpp"
#include "State.hpp"

namespace states {
	class Game : public State {
	private:
		Core* core;
	public:
		Game(Core* _core);
		void init();
		void update();
		void render();
		void unload();
	};
}