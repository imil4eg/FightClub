#ifndef CLAYMORE
#define CLAYMORE

#include "../Weapon.h"

class Claymore : public Weapon
{
private:
	Claymore() :
		Weapon{ "Claymore", 30 }
	{
	}

public:
	friend class WeaponStorage;
};

#endif // !CLAYMORE

