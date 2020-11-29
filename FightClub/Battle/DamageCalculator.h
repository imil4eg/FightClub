#ifndef DAMAGECALCULATOR_H
#define DAMAGECALCULATOR_H

#include "../Battle/Battle.h"
#include "../Characters/Character.h"
#include "../Battle/HitDirection.h"

class DamageCalculator
{
public:
	static int Calculate(Character& character, Character& target, HitDirection hitDirection)
	{
		return character.getAttributes()->getDamage() - target.getEquipment()->getArmorValue(hitDirection);
	}
};


#endif // !DAMAGECALCULATOR_H
