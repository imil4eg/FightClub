#include <boost/algorithm/string.hpp>
#include <iostream>

#include "CharacterStuff/InventoryManager.h"
#include "CharacterStuff/DynamicEquipment.h"
#include "CharacterStuff/Armors/ArmorType.h"

namespace fightclub
{
	namespace characterstuff
	{
		void InventoryManager::enterInventory(core::characters::Player& player)
		{
			while (true)
			{
				std::cout << "Please, enter the command\nCommands:\n1) Weapons\n2) Armors\n3) Current equipment \n4) Change weapon\n5) Change helmet\n"
					"6) Change cuirasse\n7) Change boots\n8) Exit\n\n";
				
				std::string command{ m_inputProcesser->getLine() };

				if (command == "1" || boost::iequals(command, "weapons"))
				{
					displayWeapons(player.getInventory().getWeapons());
				}
				else if (command == "2" || boost::iequals(command, "armors"))
				{
					displayArmors(player.getInventory().getArmors());
				}
				else if (command == "3" || boost::iequals(command, "current equipment"))
				{
					displayCurrentEquipment(player);
				}
				else if (command == "4" || boost::iequals(command, "change weapon"))
				{
					changeWeapon(player);
				}
				else if (command == "5" || boost::iequals(command, "change helmet"))
				{
					changeArmor(player, core::characterstuff::armors::ArmorType::head);
				}
				else if (command == "6" || boost::iequals(command, "change cuirasse"))
				{
					changeArmor(player, core::characterstuff::armors::ArmorType::body);
				}
				else if (command == "7" || boost::iequals(command, "change boots"))
				{
					changeArmor(player, core::characterstuff::armors::ArmorType::legs);
				}
				else if (command == "8" || boost::iequals(command, "exit"))
				{
					return;
				}
				else
				{
					std::cout << "Unrecognized command entered.\n";
				}
			}
		}

		void InventoryManager::displayCurrentEquipment(const core::characters::Character& character) const
		{
			std::cout << '\n';

			auto* weapon{ character.getWeapon() };
			std::cout << "Weapon: " << ((weapon == nullptr) ? "empty" : weapon->getName()) << '\n';

			auto* helmet{ character.getEquipment().getHelmet() };
			std::cout << "Helment: " << ((helmet == nullptr) ? "empty" : helmet->getName()) << '\n';

			auto* cuirasse{ character.getEquipment().getCuirasse() };
			std::cout << "Cuirasse: " << ((cuirasse == nullptr) ? "empty" : cuirasse->getName()) << '\n';

			auto* boots{ character.getEquipment().getBoots() };
			std::cout << "Boots: " << ((boots == nullptr) ? "empty" : boots->getName()) << '\n';

			std::cout << "Total damage: " << ((weapon == nullptr) ? 0 : weapon->getDamage()) << "\n" << "Total armor: " << character.getEquipment().getTotalArmor() << "\n\n";
		}

		void InventoryManager::displayArmors(const std::vector<std::unique_ptr<core::characterstuff::armors::Armor>>& armors, 
			core::characterstuff::armors::ArmorType armorType) const
		{
			display<std::unique_ptr<core::characterstuff::armors::Armor>>(armors, "armors",
				[armorType](const std::unique_ptr<core::characterstuff::armors::Armor>& armor)
				{
					if (armorType == core::characterstuff::armors::ArmorType::max_equipment_types ||
						armor->getType() == armorType)
						std::cout << *armor.get() << '\n';
				});
		}

		void InventoryManager::displayWeapons(const std::vector<std::unique_ptr<core::characterstuff::weapons::Weapon>>& weapons) const
		{
			display<std::unique_ptr<core::characterstuff::weapons::Weapon>>(weapons, "weapons",
				[](const std::unique_ptr<core::characterstuff::weapons::Weapon>& weapon)
				{
					std::cout << *weapon.get() << '\n';
				});
		}

		void InventoryManager::changeArmor(core::characters::Player& player, core::characterstuff::armors::ArmorType armorType)
		{
			while (true)
			{
				std::cout << '\n';

				const core::characterstuff::armors::Armor* currentArmor{ player.getEquipment().getArmor(armorType) };

				std::cout << "Current " << armorType << " is " << ((currentArmor == nullptr) ? "empty" : currentArmor->getName()) << '\n';

				std::cout << "Enter the name of " << armorType << 
							 " that you want to wear\nWrite clear to take off current " << armorType << 
							 " \nWrite exit if you want to leave this menu\n";

				displayArmors(player.getInventory().getArmors(), armorType);

				std::string armorName{ m_inputProcesser->getLine()};

				if (armorName == "Exit" || armorName == "exit")
				{
					return;
				}

				auto foundArmor{ player.getInventory().getArmorByName(armorName) };

				if (foundArmor == nullptr)
				{
					std::cout << "Armor with name " << armorName << " not found.\n";
				}
				else
				{
					auto playerEquipment{ static_cast<core::characterstuff::DynamicEquipment*>(&player.getEquipment()) };
					playerEquipment->changeArmor(foundArmor, armorType);
					std::cout << "Change from " << ((currentArmor == nullptr) ? "empty" : currentArmor->getName()) <<
						" to " << player.getEquipment().getArmor(armorType)->getName() << ".\n";
				}

				std::cout << '\n';
			}
		}

		void InventoryManager::changeWeapon(core::characters::Player& player)
		{
			while (true)
			{
				std::cout << "Current weapon " << &*player.getWeapon() << '\n';

				std::cout << "Enter the name of weapon that you want to wear\nWrite exit if you want to leave this menu:\n\n";

				displayWeapons(player.getInventory().getWeapons());

				std::string weaponName{ m_inputProcesser->getLine()};

				if (weaponName == "Exit" || weaponName == "exit")
				{
					return;
				}

				for (auto& weapon : player.getInventory().getWeapons())
				{
					if (weaponName == weapon->getName())
					{
						std::cout << "Changed " << player.getWeapon()->getName() << " to " << weapon->getName() << '\n';
						player.changeWeapon(weapon.get());
						return;
					}
				}

				std::cout << "Weapon with name " << weaponName << " does not exist.";
			}
		}

		template<typename T>
		void InventoryManager::display(const std::vector<T>& elements, std::string itemName, std::function<void(const T&)> displayFunc) const
		{
			std::cout << "\nInventory contains " << std::to_string(elements.size()) << " " << itemName << ":\n";

			for (const T& element : elements)
			{
				displayFunc(element);
			}

			std::cout << '\n';
		}
	}
}