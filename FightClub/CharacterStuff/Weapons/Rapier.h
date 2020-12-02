#ifndef RAPIER_H
#define RAPIER_H

#include "../Weapon.h"

class Rapier : public Weapon
{
public:
	Rapier() :
		Weapon{ "Rapier", 25 }
	{
	}
};

#endif // !RAPIER_H

