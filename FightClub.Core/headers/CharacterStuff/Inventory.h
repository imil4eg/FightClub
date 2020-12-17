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
				std::vector<std::unique_ptr<armors::Armor>> m_armors{};
				std::vector<std::unique_ptr<weapons::Weapon>> m_weapons{};

			public:
				Inventory() = default;

				Inventory(std::vector<std::unique_ptr<armors::Armor>> && armors, std::vector<std::unique_ptr<weapons::Weapon>> && weapons) :
					m_armors{ std::move(armors) },
					m_weapons{ std::move(weapons) }
				{
				}

				std::vector<std::unique_ptr<armors::Armor>>& getArmors() { return m_armors; }
				std::vector<std::unique_ptr<weapons::Weapon>>& getWeapons() { return m_weapons; }
				const weapons::Weapon* const getWeaponById(boost::uuids::uuid & id);
				const armors::Armor* const getArmorById(boost::uuids::uuid & id);
				const armors::Armor* getArmorByName(std::string & name);

			private:
				template<typename T>
				T* getById(std::vector<std::unique_ptr<T>>&container, boost::uuids::uuid & itemId);

				template<typename T>
				T* getBy(std::vector<std::unique_ptr<T>>&container, std::function<bool(std::unique_ptr<T>&)> condition) const;
			};
		}
	}
}