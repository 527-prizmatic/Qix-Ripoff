#include "custom_math.hpp"

const double pi = 3.1415926535;
const double euler = 2.7182818284;
const double phi = 1.6180339887;

int powi(int _a, int _exp) {
	if (_exp == 0) return 1;
	else if (_exp == 1) return _a;
	else return _a * powi(_a, _exp - 1);
}

float powi(float _a, int _exp) {
	if (_exp == 0) return 1.;
	else if (_exp == 1) return _a;
	else return _a * powi(_a, _exp - 1);
}

double powi(double _a, int _exp) {
	if (_exp == 0) return 1.;
	else if (_exp == 1) return _a;
	else return _a * powi(_a, _exp - 1);
}

float clamp(float _x, float _lower, float _upper) {
	if (_x <= _lower) return _lower;
	if (_x >= _upper) return _upper;
	return _x;
}

namespace vect {
	float magnitude(sf::Vector2f _v) {
		return sqrtf(magnitude2(_v));
	}

	float magnitude(sf::Vector2i _v) {
		return sqrtf(magnitude2(_v));
	}

	float magnitude(sf::Vector2u _v) {
		return sqrtf(magnitude2(_v));
	}

	float magnitude2(sf::Vector2f _v) {
		return _v.x * _v.x + _v.y * _v.y;
	}

	float magnitude2(sf::Vector2i _v) {
		return (float)(_v.x * _v.x + _v.y * _v.y);
	}

	float magnitude2(sf::Vector2u _v) {
		return (float)(_v.x * _v.x + _v.y * _v.y);
	}

	sf::Vector2f normalize(sf::Vector2f _v) {
		return _v / magnitude(_v);
	}

	sf::Vector2f normalize(sf::Vector2i _v) {
		float mag = magnitude(_v);
		return sf::Vector2f((float)(_v.x) / mag, (float)(_v.y) / mag);
	}

	sf::Vector2f normalize(sf::Vector2u _v) {
		float mag = magnitude(_v);
		return sf::Vector2f((float)(_v.x) / mag, (float)(_v.y) / mag);
	}

	sf::Vector2f recToPol(sf::Vector2f _v) {
		sf::Vector2f ret;
		ret.x = magnitude(_v);
		ret.y = std::atan2(_v.y, _v.x);
		return ret;
	}

	sf::Vector2f polToRec(sf::Vector2f _v) {
		sf::Vector2f ret;
		ret.x = _v.x * std::cos(_v.y);
		ret.y = _v.x * std::sin(_v.y);
		return ret;
	}
}