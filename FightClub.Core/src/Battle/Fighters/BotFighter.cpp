#include "Battle/Fighters/BotFighter.h"
#include "Common/RandomGenerator.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			namespace fighters
			{
				void BotFighter::playTurn(Fighter& target)
				{
					this->getMessageDisplayer().display("Enemy turn!\n\n");

					auto hitDirection{ static_cast<HitDirection>(common::RandomGenerator::getBetween(0, static_cast<int>(HitDirection::max_hit_direction) - 1)) };

					Fighter::hit(target, hitDirection);
				}
			}
		}
	}
}