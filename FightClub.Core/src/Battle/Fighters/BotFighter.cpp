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
				void BotFighter::askDecisions()
				{
					this->getMessageDisplayer().display("Enemy turn!\n\n");

					auto hitDirection{ static_cast<characterstuff::BodyPart>(
						common::RandomGenerator::getBetween(0, static_cast<int>(characterstuff::BodyPart::max_body_part) - 1)) };

					this->setHitDirection(hitDirection);

					auto protectingPart{ static_cast<characterstuff::BodyPart>(
						common::RandomGenerator::getBetween(0, static_cast<int>(characterstuff::BodyPart::max_body_part) - 1)) };
				
					this->setProtectingPart(protectingPart);
				}
			}
		}
	}
}