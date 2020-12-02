#ifndef POOR_BRASS_KNUCKLESS_H
#define POOR_BRASS_KNUCKLESS_H

#include "../Weapon.h"

class PoorBrassKnuckles : public Weapon
{
public:
	PoorBrassKnuckles() :
		Weapon{ "Poor brass knuckles", 5 }
	{
	}
};

#endif // !POOR_BRASS_KNUCKLESS_H

