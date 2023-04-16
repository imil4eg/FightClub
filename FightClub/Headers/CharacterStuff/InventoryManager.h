#pragma once

#include <functional>

#include "Characters/Player.h"
#include "CharacterStuff/Armors/Armor.h"
#include "CharacterStuff/Weapons/Weapon.h"
#include "CharacterStuff/IInventoryManager.h"
#include "IO/IInputProcesser.h"

namespace fightclub
{
	namespace characterstuff
	{
		class InventoryManager : public core::characterstuff::IInventoryManager
		{
		private:
			const core::io::IInputProcesser* m_inputProcesser;

		public:
			InventoryManager(const core::io::IInputProcesser& inputProcesser) :
				m_inputProcesser{ &inputProcesser }
			{
			}

			void enterInventory(core::characters::Player& player) override;
			void displayArmors(const std::vector<std::unique_ptr<core::characterstuff::armors::Armor>>& armors,
									   core::characterstuff::armors::ArmorType armorType = core::characterstuff::armors::ArmorType::max_equipment_types) const override;
			void displayWeapons(const std::vector<std::unique_ptr<core::characterstuff::weapons::Weapon>>& weapons) const override;
			void displayCurrentEquipment(const core::characters::Character& character) const override;
			void changeArmor(core::characters::Player& player, core::characterstuff::armors::ArmorType armorType) override;
			void changeWeapon(core::characters::Player& player) override;

		private:
			template<typename T>
			void display(const std::vector<T>& elements, std::string itemName, std::function<void(const T&)> displayFunc) const;
		};
	}
}