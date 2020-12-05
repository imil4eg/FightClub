#ifndef RICH_GUY_CUIRASSE_H
#define RICH_GUY_CUIRASSE_H

#include "../Armor.h"

class RichGuyCuirasse : public Armor
{
private:
	RichGuyCuirasse() :
		Armor{ "Rich Guy Cuirasse", Armor::Type::body, 5 }
	{
	}

public:
	friend class ArmorStorage;
};

#endif // !RICH_GUY_CUIRASSE_H

