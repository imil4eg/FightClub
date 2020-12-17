#pragma once

#include "Battle/HitDirection.h"
#include "CharacterStuff/Armors/Armor.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			class Equipment
			{
			public:
				virtual ~Equipment() = default;
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
}