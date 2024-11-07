#include "State.hpp"
#include "../Score.hpp"

namespace states {
	class Leaderboard : public State {
	private:
		Core* core;
		Score& score;
		char selections[3];
		char selectProgress;

		inline static sf::Text txtDisplay;
		inline static sf::Font txtFont;
		inline static sf::Sprite sprDisplay;
	public:
		Leaderboard(Core* _core);
		void init();
		void update();
		void render();
		void unload();

		std::string buildNameString();
	};
}