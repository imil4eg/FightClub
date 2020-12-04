#ifndef RICH_GUY_LEGS_H
#define RICH_GUY_LEGS_H

#include "../Armor.h"

class RichGuyLegs : public Armor
{
public:
	RichGuyLegs() :
		Armor{ Armor::Type::legs, 5 }
	{
	}
};

#endif // !RICH_GUY_LEGS_H

