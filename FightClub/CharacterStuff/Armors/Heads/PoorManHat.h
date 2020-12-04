#ifndef POOR_MAN_HAT_H
#define POOR_MAN_HAT_H

#include "../Armor.h"

class PoorManHat : public Armor
{
public:
	PoorManHat() :
		Armor{ Armor::Type::head, 1 }
	{
	}
};

#endif // !POOR_MAN_HAT_H

