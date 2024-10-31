#include "time.hpp"

namespace tutil {
	sf::Clock clock;
	float delta;

	void restart() {
		delta = clock.restart().asSeconds();
		if (delta > .1f) delta = 0.f;
	}

	float getDelta() {
		return delta;
	}
}