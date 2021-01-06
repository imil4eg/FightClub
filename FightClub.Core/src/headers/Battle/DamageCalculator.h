#pragma once

#include "Characters/Character.h"
#include "CharacterStuff/BodyPart.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			class DamageCalculator
			{
			public:
				static int Calculate(const characters::Character& character, const characters::Character& target, characterstuff::BodyPart hitDirection,
									characterstuff::BodyPart enemyProtectingPart)
				{
					int totalDamage{ character.getAttributes()->getDamage() - target.getEquipment().getArmorValue(hitDirection) };

					// If enemy correctly predicted hit direction then reduce 20% from damage.
					if (hitDirection == enemyProtectingPart)
					{
						int twentyPercentFromDamage{ (totalDamage * 20) / 100 };
						totalDamage -= twentyPercentFromDamage;
					}

					return totalDamage;
				}
			};
		}
	}
}