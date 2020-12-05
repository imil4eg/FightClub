#ifndef RICH_GUY_HAT_H
#define RICH_GUT_HAT_H

#include "../Armor.h"

class RichGuyHat : public Armor
{
private:
	RichGuyHat() :
		Armor{ "Rich Guy Hat", Armor::Type::head, 5 }
	{
	}

public:
	friend class ArmorStorage;
};

#endif // !RICH_GUY_HAT_H

