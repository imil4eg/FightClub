#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Armors/Armor.h"
#include "../Battle/HitDirection.h"

namespace fightclub
{
	namespace characterstuff
	{
		class Equipment
		{
		public:
			virtual const armors::Armor* getHelmet() const = 0;
			virtual const armors::Armor* getCuirasse() const = 0;
			virtual const armors::Armor* getBoots() const = 0;
			int getArmorValue(battle::HitDirection hitDirection) const;
		};
	}
}

#endif // !EQUIPMENT_H

