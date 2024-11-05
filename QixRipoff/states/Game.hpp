#pragma once
#include "../toolbox/toolbox.hpp"
#include "State.hpp"
#include "../GameField.hpp"
#include "../Player.hpp"
#include "../Score.hpp"

namespace states {
	class Game : public State {
	private:
		Core* core;
		GameField field;
		Player player;
		Score score;
	public:
		Game(Core* _core);
		void init();
		void update();
		void render();
		void unload();
	};
}