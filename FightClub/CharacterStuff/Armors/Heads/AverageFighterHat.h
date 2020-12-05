#ifndef AVERAGE_FIGHTER_HAT_H
#define AVERAGE_FIGHTER_HAT_H

#include "../Armor.h"

class AverageFighterHat : public Armor
{
private:
	AverageFighterHat() :
		Armor{ "Average Fighter Hat", Armor::Type::head, 3 }
	{
	}

public:
	friend class ArmorStorage;
};

#endif // !AVERAGE_FIGHTER_HAT_H

