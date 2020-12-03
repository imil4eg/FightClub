#ifndef BRASS_KNUCKLES_WITH_KNFIE
#define BRASS_KNUCKLES_WITH_KNFIE

#include "../Weapon.h"

class BrassKnucklesWithKnife : public Weapon
{
private:
	BrassKnucklesWithKnife() :
		Weapon("Brass knuckles with knife", 10)
	{
	}

public:
	friend class WeaponStorage;
};

#endif // !BRASS_KNUCKLES_WITH_KNFIE

