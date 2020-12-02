#ifndef BRASS_KNUCKLES_WITH_KNFIE
#define BRASS_KNUCKLES_WITH_KNFIE

#include "../Weapon.h"

class BrassKnucklesWithKnife : public Weapon
{
public:
	BrassKnucklesWithKnife() :
		Weapon("Brass knuckles with knife", 10)
	{
	}
};

#endif // !BRASS_KNUCKLES_WITH_KNFIE

