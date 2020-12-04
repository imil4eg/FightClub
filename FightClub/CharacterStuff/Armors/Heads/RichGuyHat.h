#ifndef RICH_GUY_HAT_H
#define RICH_GUT_HAT_H

#include "../Armor.h"

class RichGuyHat : public Armor
{
public:
	RichGuyHat() :
		Armor{ Armor::Type::head, 5 }
	{
	}
};

#endif // !RICH_GUY_HAT_H

