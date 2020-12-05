#ifndef POOR_MAN_LEGS_H
#define POOR_MAN_LEGS_H

#include "../Armor.h"

class PoorManLegs : public Armor
{
private:
	PoorManLegs() :
		Armor{ "Poorn Man Boots", Armor::Type::legs, 1 }
	{
	}

public:
	friend class ArmorStorage;
};

#endif // !POOR_MAN_LEGS_H

