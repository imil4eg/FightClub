#pragma once

#include "Characters/Character.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			class DamageCalculator
			{
			public:
				static int Calculate(characters::Character& character, characters::Character& target, HitDirection hitDirection)
				{
					return character.getAttributes()->getDamage() - target.getEquipment()->getArmorValue(hitDirection);
				}
			};
		}
	}
}