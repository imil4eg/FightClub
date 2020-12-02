#ifndef KNIFE
#define KNIFE

#include "../Weapon.h"

class Knife : public Weapon
{
public:
	Knife() :
		Weapon{ "Knife", 10 }
	{
	}
};

#endif // !KNIFE

