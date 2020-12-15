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
			const armors::Armor* getArmor(armors::ArmorType armorType) const;
			int getArmorValue(battle::HitDirection hitDirection) const;
			int getTotalArmor() const;

		private:
			int getArmorValue(const armors::Armor* armor) const;
		};
	}
}

#endif // !EQUIPMENT_H

