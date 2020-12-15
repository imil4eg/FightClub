#pragma once

#include <functional>

#include "IInventoryManager.h"

namespace fightclub
{
	namespace characterstuff
	{
		class InventoryManager : public IInventoryManager
		{
		public:
			void enterMenu(characters::Player& player) override;
			void displayCurrentEquipment(characters::Character& character);
			void displayWeapons(std::vector<std::unique_ptr<characterstuff::weapons::Weapon>>& weapons);
			void displayArmors(std::vector<std::unique_ptr<characterstuff::armors::Armor>>& armors);
			void changeWeapon(std::vector<std::unique_ptr<characterstuff::weapons::Weapon>>& weapons, characters::Player& character);

		private:
			template<typename T>
			void display(std::vector<T>& elements, std::string itemName, std::function<void(T&)> displayFunc);
			void changeHelment(characters::Player& player);
			void changeCuirass(characters::Player& player);
			void changeBoots(characters::Player& player);
			void changeArmor(characters::Player& player, fightclub::characterstuff::armors::ArmorType armorType);
		};
	}
}
