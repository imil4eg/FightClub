#include <exception>
#include <iostream>

#include "CharacterStuff/InventoryManager.h"
#include "IO/InputProcesser.h"

namespace fightclub
{
	namespace characterstuff
	{
		void InventoryManager::enterMenu()
		{
			while (true)
			{
				Command command{ InputProcesser::askMenuCommand() };

				switch (command)
				{
				case Command::weapons:
					displayWeapons();
					break;
				case Command::armors:
					displayArmors();
					break;
				case Command::equipment:
					displayCurrentEquipment();
					break;
				case Command::exit:
					return;
				default:
					throw std::exception("Not implemented menu command type.");
				}
			}
		}

		void InventoryManager::displayCurrentEquipment()
		{
			auto* weapon{ m_playerConfig->getUserModelData().character->getWeapon() };
			std::cout << "Weapon: " << ((weapon == nullptr) ? "empty" : weapon->getName()) << '\n';

			auto* equipment{ m_playerConfig->getUserModelData().character->getEquipment() };
			auto* helmet{ equipment->getHelment() };
			std::cout << "Helment: " << ((helmet == nullptr) ? "empty" : helmet->getName()) << '\n';

			auto* cuirasse{ equipment->getCuirasse() };
			std::cout << "Cuirasse: " << ((cuirasse == nullptr) ? "empty" : cuirasse->getName()) << '\n';

			auto* boots{ equipment->getBoots() };
			std::cout << "Boots: " << ((boots == nullptr) ? "empty" : boots->getName()) << '\n';
		}

		void InventoryManager::displayWeapons()
		{
			display<std::unique_ptr<Weapon>> (m_playerConfig->getUserModelData().weapons, "weapons",
				[](std::unique_ptr<Weapon>& weapon) {
					std::cout << weapon->getName() << " | weapon: " << weapon->getDamage();
				});
		}

		void InventoryManager::displayArmors()
		{
			display<std::unique_ptr<Armor>>(m_playerConfig->getUserModelData().armors, "armors",
				[](std::unique_ptr<Armor>& armor)
				{
					std::cout << armor->getName() << " | armor: " << armor->getArmor();
				});
		}

		template<typename T>
		void InventoryManager::display(std::vector<T>& elements, std::string itemName, std::function<void(T&)> displayFunc)
		{
			std::cout << "Inventory contains " << elements.size() << " of " << itemName << ":\n";

			for (auto& element : elements)
			{
				displayFunc(element);
				std::cout << "\n";
			}
		}
	}
}