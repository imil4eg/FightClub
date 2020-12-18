//#pragma once
//
//#include <functional>
//
//#include "Characters/Character.h"
//#include "IInventoryManager.h"
//
//namespace fightclub
//{
//	namespace characterstuff
//	{
//		class InventoryManager : public IInventoryManager
//		{
//		public:
//			void enterMenu(core::characters::Player& player) override;
//			void displayCurrentEquipment(core::characters::Character& character);
//			void displayWeapons(std::vector<std::unique_ptr<core::characterstuff::weapons::Weapon>>& weapons);
//			void displayArmors(std::vector<std::unique_ptr<core::characterstuff::armors::Armor>>& armors, core::characterstuff::armors::ArmorType armorType = core::characterstuff::armors::ArmorType::max_equipment_types);
//			void changeWeapon(std::vector<std::unique_ptr<core::characterstuff::weapons::Weapon>>& weapons, core::characters::Player& character);
//
//		private:
//			template<typename T>
//			void display(std::vector<T>& elements, std::string itemName, std::function<void(T&)> displayFunc);
//			void changeHelment( core::characters::Player& player);
//			void changeCuirasse(core::characters::Player& player);
//			void changeBoots(   core::characters::Player& player);
//			void changeArmor(   core::characters::Player& player, core::characterstuff::armors::ArmorType armorType);
//		};
//	}
//}
