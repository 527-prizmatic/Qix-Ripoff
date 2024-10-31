#pragma once
#include "../toolbox/toolbox.hpp"

class Core;

namespace states {
	/// Interface for gamestates
	class State {
	protected:
		Core* core;
	public:
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void unload() = 0;
	};
}