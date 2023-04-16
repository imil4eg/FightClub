#pragma once

#include <memory>
#include <vector>

#include "CharacterStuff/Armors/Armor.h"
#include "CharacterStuff/Weapons/Weapon.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			class Inventory
			{
			private:
				struct Impl;
				std::unique_ptr<Impl> pImpl;

			public:
				Inventory();

				Inventory(std::vector<std::unique_ptr<armors::Armor>>&& armors, std::vector<std::unique_ptr<weapons::Weapon>>&& weapons);

				~Inventory();

				std::vector<std::unique_ptr<armors::Armor>>& getArmors();
				std::vector<std::unique_ptr<weapons::Weapon>>& getWeapons();
				const weapons::Weapon* const getWeaponById(boost::uuids::uuid & id);
				const armors::Armor* const getArmorById(boost::uuids::uuid & id);
				const armors::Armor* getArmorByName(std::string & name);
			};
		}
	}
}