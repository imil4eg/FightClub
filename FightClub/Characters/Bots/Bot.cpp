#include "Characters/Bots/Bot.h"
#include "Battle/DamageCalculator.h"
#include "IO/MessageDisplayer.h"
#include "Battle/HitDirection.h"
#include "Common/RandomGenerator.h"

namespace fightclub
{
	namespace characters
	{
		namespace bots
		{
			void Bot::hit(Character& enemy, battle::HitDirection hitDirection)
			{
				int damage = battle::DamageCalculator::Calculate(*this, enemy, hitDirection);
				io::MessageDisplayer::displayEnemyHit(damage, hitDirection);

				Character::hit(enemy, damage);

				io::MessageDisplayer::displayPlayerHP(enemy.getAttributes()->getHp());
			}

			void Bot::playTurn(Character& player)
			{
				auto hitDirection{ static_cast<battle::HitDirection>(common::RandomGenerator::getBetween(0, static_cast<int>(battle::HitDirection::max_hit_direction) - 1)) };

				this->hit(player, hitDirection);
			}
		}
	}
}