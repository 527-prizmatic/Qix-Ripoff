#include "BonusSpeedPlayer.hpp"
#include "Player.hpp"

BonusSpeedPlayer::BonusSpeedPlayer()
{
	this->core = nullptr;
	this->field = nullptr;
	this->pos = sf::Vector2u(0, 0);
	this->isActivated = false;
	this->timerAprrition = 10;
	this->timerEffectif = 5;
}

BonusSpeedPlayer::BonusSpeedPlayer(Core* _core, GameField* _field, sf::Vector2u _pos) : Bonus(_core, _field, _pos)
{
	this->isActivated = false;
	this->timerAprrition = 10;
	this->timerEffectif = 5;
}

void BonusSpeedPlayer::update(GameField* _field, Player* _plr)
{
}

void BonusSpeedPlayer::draw(GameField* _field)
{
}
