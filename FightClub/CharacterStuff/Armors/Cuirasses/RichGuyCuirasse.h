#ifndef RICH_GUY_CUIRASSE_H
#define RICH_GUY_CUIRASSE_H

#include "../Armor.h"

class RichGuyCuirasse : public Armor
{
public:
	RichGuyCuirasse() :
		Armor{ Armor::Type::body, 5 }
	{
	}
};

#endif // !RICH_GUY_CUIRASSE_H

