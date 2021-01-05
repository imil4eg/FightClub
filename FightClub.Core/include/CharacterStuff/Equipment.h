#pragma once

#include "CharacterStuff/Armors/Armor.h"
#include "CharacterStuff/BodyPart.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			class Equipment
			{
			private:
				struct Impl;
				std::unique_ptr<Impl> pImpl;

			public:
				Equipment();
				virtual ~Equipment();
				virtual const armors::Armor* getHelmet() const = 0;
				virtual const armors::Armor* getCuirasse() const = 0;
				virtual const armors::Armor* getBoots() const = 0;
				const armors::Armor* getArmor(armors::ArmorType armorType) const;
				int getArmorValue(characterstuff::BodyPart hitDirection) const;
				int getTotalArmor() const;
			};
		}
	}
}