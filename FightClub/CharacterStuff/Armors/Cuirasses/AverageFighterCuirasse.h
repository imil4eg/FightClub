#ifndef AVERAGE_FIGHTER_CUIRASSE_H
#define AVERAGE_FIGHTER_CUIRASSE_H

#include "../Armor.h"

class AverageFighterCuirasse : public Armor
{
public:
	AverageFighterCuirasse() :
		Armor{ "Average Cuirasse", Armor::Type::body, 3 }
	{
	}
};

#endif // !AVERAGE_FIGHTER_CUIRASSE_H

