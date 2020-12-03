#ifndef KNIFE
#define KNIFE

#include "../Weapon.h"

class Knife : public Weapon
{
private:
	Knife() :
		Weapon{ "Knife", 10 }
	{
	}

public:
	friend class WeaponStorage;
};

#endif // !KNIFE

