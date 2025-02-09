#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <array>
#include <optional>
#include <vector>
#include <sstream>
#include <algorithm>


#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

#include "time.hpp"
#include "random.hpp"
#include "custom_math.hpp"
#include "interpolation.hpp"
#include "../controls/Controls.hpp"
#include "../Preinit.hpp"

namespace ctrl {
	typedef enum ButtonState {
		IDLE,
		CLICK,
		HOLD,
		RELEASE
	} ButtonState;
}