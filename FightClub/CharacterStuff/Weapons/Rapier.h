#ifndef RAPIER_H
#define RAPIER_H

#include "../Weapon.h"

class Rapier : public Weapon
{
private:
	Rapier() :
		Weapon{ "Rapier", 25 }
	{
	}

public:
	friend class WeaponStorage;
};

#endif // !RAPIER_H

