#ifndef POOR_MAN_LEGS_H
#define POOR_MAN_LEGS_H

#include "../Armor.h"

class PoorManLegs : public Armor
{
public:
	PoorManLegs() :
		Armor{ Armor::Type::legs, 1 }
	{
	}
};

#endif // !POOR_MAN_LEGS_H

