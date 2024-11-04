#include "Sparks.hpp"

sf::RectangleShape rectangleSparks(sf::Vector2f(10, 10));

Sparks::Sparks()
{
	this->dir = DOWN;
	Sparks::sparks.push_back(*this);
}

Sparks::Sparks(Core* _core, GameField* _field, sf::Vector2u _pos, Direction _dir):Ennemy(_core, _field, _pos)
{
	this->dir = _dir;
	Sparks::sparks.push_back(*this);
}

void Sparks::update()
{
}

void Sparks::draw()
{
	for (auto& spark : Sparks::sparks)
	{
		rectangleSparks.setPosition(sf::Vector2f(spark.getPos().x * 10, spark.getPos().y * 10));
		rectangleSparks.setFillColor(sf::Color::Red);
		this->core->getWindow().draw(rectangleSparks);
	}
}
