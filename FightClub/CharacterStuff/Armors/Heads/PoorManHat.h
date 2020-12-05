#ifndef POOR_MAN_HAT_H
#define POOR_MAN_HAT_H

#include "../Armor.h"

class PoorManHat : public Armor
{
private:
	PoorManHat() :
		Armor{ "Poor Man Hat", Armor::Type::head, 1 }
	{
	}

public:
	friend class ArmorStorage;
};

#endif // !POOR_MAN_HAT_H

