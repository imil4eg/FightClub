#include "Bot.h"
#include "../../Battle/DamageCalculator.h"
#include "../../IO/MessageDisplayer.h"
#include "../../Battle/HitDirection.h"
#include "../../Common/RandomGenerator.h"

void Bot::hit(Character& enemy, HitDirection hitDirection)
{
	int damage = DamageCalculator::Calculate(*this, enemy, hitDirection);
	MessageDisplayer::displayEnemyHit(damage, hitDirection);

	Character::hit(enemy, damage);

	MessageDisplayer::displayPlayerHP(enemy.getAttributes()->getHp());
}

void Bot::playTurn(Character& player)
{
	auto hitDirection{ static_cast<HitDirection>(RandomGenerator::getBetween(0, static_cast<int>(HitDirection::max_hit_direction) - 1)) };

	this->hit(player, hitDirection);
}