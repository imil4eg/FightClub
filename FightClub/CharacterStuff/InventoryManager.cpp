#include <exception>
#include <iostream>

#include "CharacterStuff/InventoryManager.h"
#include "IO/MessageDisplayer.h"
#include "IO/InputProcesser.h"

namespace fightclub
{
	namespace characterstuff
	{
		void InventoryManager::enterMenu(characters::Player& player)
		{
			while (true)
			{
				common::Command command{ io::InputProcesser::askMenuCommand() };

				switch (command)
				{
				case common::Command::weapons:
					displayWeapons(player.getInventory().getWeapons());
					break;
				case common::Command::armors:
					displayArmors(player.getInventory().getArmors());
					break;
				case common::Command::equipment:
					displayCurrentEquipment(player);
					break;
				case common::Command::change_weapon:
					changeWeapon(player.getInventory().getWeapons(), player);
					break;
				case common::Command::change_helmet:
					break;
				case common::Command::change_cuirass:
					break;
				case common::Command::change_boots:
					break;
				case common::Command::exit:
					return;
				default:
					throw std::exception("Not implemented menu command type.");
				}
			}
		}

		void InventoryManager::displayCurrentEquipment(characters::Character& character)
		{
			auto* weapon{ character.getWeapon() };
			std::cout << "Weapon: " << ((weapon == nullptr) ? "empty" : weapon->getName()) << '\n';

			auto* equipment{ character.getEquipment() };
			auto* helmet{ equipment->getHelmet() };
			std::cout << "Helment: " << ((helmet == nullptr) ? "empty" : helmet->getName()) << '\n';

			auto* cuirasse{ equipment->getCuirasse() };
			std::cout << "Cuirasse: " << ((cuirasse == nullptr) ? "empty" : cuirasse->getName()) << '\n';

			auto* boots{ equipment->getBoots() };
			std::cout << "Boots: " << ((boots == nullptr) ? "empty" : boots->getName()) << '\n';
		}

		void InventoryManager::displayWeapons(std::vector<std::unique_ptr<characterstuff::weapons::Weapon>>& weapons)
		{
			display<std::unique_ptr<characterstuff::weapons::Weapon>> (weapons, "weapons",
				[](std::unique_ptr<characterstuff::weapons::Weapon>& weapon) {
					std::cout << *weapon;
				});
		}

		void InventoryManager::displayArmors(std::vector<std::unique_ptr<characterstuff::armors::Armor>>& armors)
		{
			display<std::unique_ptr<characterstuff::armors::Armor>>(armors, "armors",
				[](std::unique_ptr<characterstuff::armors::Armor>& armor)
				{
					std::cout << *armor;
				});
		}

		void InventoryManager::changeWeapon(std::vector<std::unique_ptr<characterstuff::weapons::Weapon>>& weapons, characters::Player& player)
		{
			while (true)
			{
				std::cout << "Current weapon " << *player.getWeapon() << '\n';

				std::cout << "Enter the name of weapon that you want to wear\nWrite exit if you want to leave this menu:\n";

				displayWeapons(weapons);

				io::MessageDisplayer::cmdLineBeggining();

				std::string weaponName{};
				std::getline(std::cin, weaponName);

				if (weaponName == "Exit" || weaponName == "exit")
				{
					return;
				}

				for (auto& weapon : weapons)
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

		void InventoryManager::changeHelment(std::vector<std::unique_ptr<characterstuff::armors::Armor>>& armors, characters::Player& player)
		{
			changeArmor(armors, player, armors::ArmorType::head);
		}

		void InventoryManager::changeCuirass(std::vector<std::unique_ptr<characterstuff::armors::Armor>>& armors, characters::Player& player)
		{
			changeArmor(armors, player, armors::ArmorType::body);
		}

		void InventoryManager::changeBoots(std::vector<std::unique_ptr<characterstuff::armors::Armor>>& armors, characters::Player& player)
		{
			changeArmor(armors, player, armors::ArmorType::legs);
		}

		void InventoryManager::changeArmor(std::vector<std::unique_ptr<characterstuff::armors::Armor>>& armors, characters::Player& player, fightclub::characterstuff::armors::ArmorType armorType)
		{	
			const characterstuff::armors::Armor* currentArmor;

			switch (armorType)
			{
			case armors::ArmorType::head:
				currentArmor = player.getEquipment()->getHelmet();
				break;
			case armors::ArmorType::body:
				currentArmor = player.getEquipment()->getCuirasse();
				break;
			case armors::ArmorType::legs:
				currentArmor = player.getEquipment()->getBoots();
				break;
			default:
				throw std::exception("Not implemented armor type.");
			}

			while (true)
			{
				std::cout << "Current " << armorType << " is " << currentArmor << '\n';

				std::cout << "Enter the name of " << armorType << " that you want to wear\nWrite clear to take off current " << armorType << " \nWrite exit if you want to leave this menu\n";

				for (auto& armor : armors)
				{
					if (armor->getType() == armorType)
					{
						std::cout << armor;
						std::cout << '\n';
					}
				}

				std::string armorName{};
				std::getline(std::cin, armorName);

				if (armorName == "Exit" || armorName == "exit")
				{
					return;
				}
				else if (armorName == "Clear" || armorName == "clear")
				{

				}
			}
		}

		template<typename T>
		void InventoryManager::display(std::vector<T>& elements, std::string itemName, std::function<void(T&)> displayFunc)
		{
			std::cout << "Inventory contains " << elements.size() << " " << itemName << ":\n";

			for (auto& element : elements)
			{
				displayFunc(element);
				std::cout << "\n";
			}
		}
	}
}