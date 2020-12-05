#ifndef AVERAGE_FIGHTER_LEGS_H
#define AVERAGE_FIGHTER_LEGS_H

#include "../Armor.h"

class AverageFighterLegs : public Armor
{
private:
	AverageFighterLegs() :
		Armor{ "Average Fighter Boots", Armor::Type::legs, 3 }
	{
	}

public:
	friend class ArmorStorage;
};

#endif // !AVERAGE_FIGHTER_LEGS_H

