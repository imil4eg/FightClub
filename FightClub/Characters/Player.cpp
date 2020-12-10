#include <boost/lexical_cast.hpp>

#include "Battle/DamageCalculator.h"
#include "IO/MessageDisplayer.h"
#include "IO/InputProcesser.h"
#include "Characters/Player.h"

void Player::playTurn(Character& target)
{
	MessageDisplayer::displayPlayerTurn();

	auto hitDirection{ InputProcesser::askHitDirection() };

	this->hit(target, hitDirection);
}

void Player::hit(Character& enemy, HitDirection hitDirection)
{
	int damage = DamageCalculator::Calculate(*this, enemy, hitDirection);
	
	MessageDisplayer::displayPlayerHit(damage, hitDirection);

	Character::hit(enemy, damage);

	MessageDisplayer::displayEnemyHP(enemy.getAttributes()->getHp());
}