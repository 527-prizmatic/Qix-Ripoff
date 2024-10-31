#pragma once
#include "toolbox.hpp"

extern const double pi;
extern const double euler;
extern const double phi;

/// Quick square
template <typename T> T pow2(T _a) { return _a * _a; }
/// Quick cube
template <typename T> T pow3(T _a) { return _a * _a * _a; }
/// Quick fourth power
template <typename T> T pow4(T _a) { return _a * _a * _a * _a; }

/// Quick power function for integer exponents, because the implementation of pow() is horrendous
int powi(int _a, int _exp);
float powi(float _a, int _exp);
double powi(double _a, int _exp);

float clamp(float _x, float _lower, float _upper);

namespace vect {
	float magnitude(sf::Vector2f _v);
	float magnitude(sf::Vector2i _v);
	float magnitude(sf::Vector2u _v);

	float magnitude2(sf::Vector2f _v);
	float magnitude2(sf::Vector2i _v);
	float magnitude2(sf::Vector2u _v);

	sf::Vector2f normalize(sf::Vector2f _v);
	sf::Vector2f normalize(sf::Vector2i _v);
	sf::Vector2f normalize(sf::Vector2u _v);
}