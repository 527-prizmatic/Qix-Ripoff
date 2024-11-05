#pragma once
#include "../toolbox/toolbox.hpp"
#include "State.hpp"
#include "../GameField.hpp"
#include "../Player.hpp"
#include "../Score.hpp"

extern const float difficulty;

namespace states {
	class Game : public State {
	private:
		Core* core;
		GameField field;
		Player player;
		Score score;
		int level;

		static sf::Text txtDisplay;
		static sf::Font txtFont;
	public:
		Game(Core* _core);
		void init();
		void update();
		void render();
		void unload();

		void renderHUD();
	};
}