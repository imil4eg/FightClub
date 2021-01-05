#include "Battle/Fighters/BotFighter.h"
#include "Common/RandomGenerator.h"
#include "CharacterStuff/BodyPart.h"

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

					auto hitDirection{ static_cast<characterstuff::BodyPart>(
						common::RandomGenerator::getBetween(0, static_cast<int>(characterstuff::BodyPart::max_body_part) - 1)) };

					Fighter::hit(target, hitDirection);
				}
			}
		}
	}
}