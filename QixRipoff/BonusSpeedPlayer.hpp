#pragma once
#include "Core.hpp"
#include "Bonus.hpp"
class GameField;
class Player;


class BonusSpeedPlayer : public Bonus
{ 
private:
	bool isActivated;
	float timerAprrition;
	float timerEffectif;
public:
	BonusSpeedPlayer();
	BonusSpeedPlayer(Core* _core, GameField* _field, sf::Vector2u _pos);
	void update(GameField* _field, class Player* _plr);
	void draw(GameField* _field);
};

