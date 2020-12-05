#ifndef RICH_GUY_LEGS_H
#define RICH_GUY_LEGS_H

#include "../Armor.h"

class RichGuyLegs : public Armor
{
private:
	RichGuyLegs() :
		Armor{ "Rich Guy Boots", Armor::Type::legs, 5 }
	{
	}

public:
	friend class ArmorStorage;
};

#endif // !RICH_GUY_LEGS_H

