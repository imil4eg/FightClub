#pragma once

#include <memory>
#include <vector>

#include "Armors/Armor.h"
#include "Weapons/Weapon.h"

namespace fightclub
{
	namespace characterstuff
	{
		class Inventory
		{
		private:
			std::vector<std::unique_ptr<Armor>> m_armors{};
			std::vector<std::unique_ptr<Weapon>> m_weapons{};

		public:
			Inventory() = default;

			Inventory(std::vector<std::unique_ptr<Armor>>&& armors, std::vector<std::unique_ptr<Weapon>>&& weapons) : 
				m_armors{ std::move(armors) },
				m_weapons{ std::move(weapons) }
			{
			}

			std::vector<std::unique_ptr<Armor>>& getArmors() { return m_armors; }
			std::vector<std::unique_ptr<Weapon>>& getWeapons() { return m_weapons; }
			const Weapon* const getWeaponById(boost::uuids::uuid& id);
		};
	}
}