#pragma once
#include "toolbox.hpp"

#define ITP(a, b, t) (((b) - (a)) * (t) + (a))

namespace itp {
	template <typename T> T scalar(T _a, T _b, float _t, float _method(float _x)) {
		float it = _method(_t);
		return ITP(_a, _b, it);
	}

	template <typename T> sf::Vector2<T> vector(sf::Vector2<T> _a, sf::Vector2<T> _b, float _t, float _method(float _x)) {
		float it = _method(_t);
		return sf::Vector2<T>(ITP(_a.x, _b.x, it), ITP(_a.y, _b.y, it));
	}

	sf::Color color(sf::Color _a, sf::Color _b, float _t, float _method(float _x));

	namespace formula {
		float Nearest(float _x);
		float Linear(float _x);

		float Square(float _x);
		float Cubic(float _x);
		float Quartic(float _x);

		float InvSquare(float _x);
		float InvCubic(float _x);
		float InvQuartic(float _x);

		float Smooth(float _x);
		float Smoother(float _x);
		float Smoothest(float _x);
		float Smoothester(float _x);
	}
}