#ifndef POOR_MAN_CUIRASSE_H
#define POOR_MAN_CUIRASSE_H

#include "../Armor.h"

class PoorManCuirasse : public Armor
{
public:
	PoorManCuirasse() :
		Armor{ "Poor man Cuirasse", Armor::Type::body, 1 }
	{
	}
};

#endif // !POOR_MAN_CUIRASSE_H

