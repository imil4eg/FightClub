#ifndef POOR_MAN_CUIRASSE_H
#define POOR_MAN_CUIRASSE_H

#include "../Armor.h"

class PoorManCuirasse : public Armor
{
private:
	PoorManCuirasse() :
		Armor{ "Poor man Cuirasse", Armor::Type::body, 1 }
	{
	}

public:
	friend class ArmorStorage;
};

#endif // !POOR_MAN_CUIRASSE_H

