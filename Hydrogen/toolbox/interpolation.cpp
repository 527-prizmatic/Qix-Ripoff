#include "interpolation.hpp"

namespace itp {
	sf::Color color(sf::Color _a, sf::Color _b, float _t, float _method(float _x)) {
		float it = _method(_t);
		return sf::Color(
			ITP(_a.r, _b.r, it),
			ITP(_a.g, _b.g, it),
			ITP(_a.b, _b.b, it),
			ITP(_a.a, _b.a, it)
		);
	}

	namespace formula {
		float Nearest(float _x) { return _x >= .5f ? 1.f : 0.f; }
		float Linear(float _x) { return clamp(_x, 0.f, 1.f); }

		float Square(float _x) { return clamp(pow2(_x), 0.f, 1.f); }
		float Cubic(float _x) { return clamp(pow3(_x), 0.f, 1.f); }
		float Quartic(float _x) { return clamp(pow4(_x), 0.f, 1.f); }

		float InvSquare(float _x) { return clamp(1.f - pow2(1.f - _x), 0.f, 1.f); }
		float InvCubic(float _x) { return clamp(1.f - pow3(1.f - _x), 0.f, 1.f); }
		float InvQuartic(float _x) { return clamp(1.f - pow4(1.f - _x), 0.f, 1.f); }

		float Smooth(float _x) { return clamp(pow2(_x) * (3.f - 2.f * _x), 0.f, 1.f); }
		float Smoother(float _x) { return clamp(pow3(_x) * ((6.f * _x - 15.f) * _x + 10.f), 0.f, 1.f); }
		float Smoothest(float _x) { return clamp(pow4(_x) * (35.f + _x * (_x * (70.f - _x * 20.f) - 84.f)), 0.f, 1.f); }
		float Smoothester(float _x) { return clamp(powi(_x, 5) * (126.f + _x * (-420.f + _x * (540.f + _x * (-315.f + _x * 70.f)))), 0.f, 1.f); }
	}
}