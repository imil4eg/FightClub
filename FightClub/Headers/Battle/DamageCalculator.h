#ifndef DAMAGECALCULATOR_H
#define DAMAGECALCULATOR_H

#include "../Battle/Battle.h"
#include "../Characters/Character.h"
#include "../Battle/HitDirection.h"

namespace fightclub
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

#endif // !DAMAGECALCULATOR_H
