#ifndef AVERAGE_FIGHTER_HAT_H
#define AVERAGE_FIGHTER_HAT_H

#include "../Armor.h"

class AverageFighterHat : public Armor
{
public:
	AverageFighterHat() :
		Armor{ Armor::Type::head, 3 }
	{
	}
};

#endif // !AVERAGE_FIGHTER_HAT_H

