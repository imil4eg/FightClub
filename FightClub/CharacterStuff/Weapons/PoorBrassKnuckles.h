#ifndef POOR_BRASS_KNUCKLESS_H
#define POOR_BRASS_KNUCKLESS_H

#include "../Weapon.h"

class PoorBrassKnuckles : public Weapon
{
private:
	PoorBrassKnuckles() :
		Weapon{ "Poor brass knuckles", 5 }
	{
	}

public:
	friend class WeaponStorage;
};

#endif // !POOR_BRASS_KNUCKLESS_H

