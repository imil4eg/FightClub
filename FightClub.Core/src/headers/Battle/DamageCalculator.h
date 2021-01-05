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
				static int Calculate(const characters::Character& character, const characters::Character& target, characterstuff::BodyPart hitDirection)
				{
					return character.getAttributes()->getDamage() - target.getEquipment().getArmorValue(hitDirection);
				}
			};
		}
	}
}