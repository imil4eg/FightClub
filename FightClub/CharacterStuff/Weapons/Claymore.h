#ifndef CLAYMORE
#define CLAYMORE

#include "../Weapon.h"

class Claymore : public Weapon
{
public:
	Claymore() :
		Weapon{ "Claymore", 30 }
	{
	}
};

#endif // !CLAYMORE

