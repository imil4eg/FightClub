#pragma once

#include <vector>

#include "Characters/Player.h"
#include "CharacterStuff/Armors/Armor.h"
#include "CharacterStuff/Weapons/Weapon.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			class IInventoryManager
			{
			public:
				virtual ~IInventoryManager() = default;
				
				virtual void enterInventory(characters::Player& player) = 0;
				virtual void displayArmors(const std::vector<std::unique_ptr<characterstuff::armors::Armor>>& armors,
										   characterstuff::armors::ArmorType armorType = characterstuff::armors::ArmorType::max_equipment_types) const = 0;
				virtual void displayWeapons(const std::vector<std::unique_ptr<characterstuff::weapons::Weapon>>& weapons) const = 0;
				virtual void displayCurrentEquipment(const characters::Character& character) const = 0;
				virtual void changeArmor(characters::Player& player, characterstuff::armors::ArmorType armorType) = 0;
				virtual void changeWeapon(characters::Player& player) = 0;
			};
		}
	}
}