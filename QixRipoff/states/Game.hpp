#pragma once
#include "../toolbox/toolbox.hpp"
#include "State.hpp"
#include "../GameField.hpp"

namespace states {
	class Game : public State {
	private:
		Core* core;
		GameField field;
	public:
		Game(Core* _core);
		void init();
		void update();
		void render();
		void unload();
	};
}