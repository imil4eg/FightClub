#include <iostream>
#include <fstream>

#include "Characters/Character.h"
#include "IO/MessageDisplayer.h"
#include "IO/InputProcesser.h"

namespace fightclub
{
	namespace io
	{
		battle::HitDirection InputProcesser::askHitDirection()
		{
			battle::HitDirection hitDirection{};
			do
			{
				std::cout << "Choose where will you hit the opponen:\n1) Head\n2) Body\n3) Legs\n";
				MessageDisplayer::cmdLineBeggining();
				std::string input;
				std::cin >> input;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				if (input == "Head")
				{
					hitDirection = battle::HitDirection::head;
				}
				else if (input == "Body")
				{
					hitDirection = battle::HitDirection::body;
				}
				else if (input == "Legs")
				{
					hitDirection = battle::HitDirection::legs;
				}
				else
				{
					hitDirection = battle::HitDirection::max_hit_direction;
				}

			} while (hitDirection == battle::HitDirection::max_hit_direction);

			return static_cast<battle::HitDirection>(hitDirection);
		}

		common::Command InputProcesser::askCommand()
		{
			do
			{
				std::cout << "Please, enter the command\nCommands:\n1) Play\n2) Customize character\n3) Inventory\n4) Exit\n\n";
				MessageDisplayer::cmdLineBeggining();
				std::string command;
				std::cin >> command;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				if (command == "1" || command == "Play" || command == "play")
				{
					return common::Command::play;
				}
				else if (command == "2" || command == "Customize character" || command == "customize character")
				{
					return common::Command::customize_character;
				}
				else if (command == "3" || command == "Inventory" || command == "inventory")
				{
					return common::Command::inventory;
				}
				else if (command == "4" || command == "Exit" || command == "exit")
				{
					return common::Command::exit;
				}
				else
				{
					std::cout << "Unrecognized command entered.\n";
				}

			} while (true);
		}

		common::Command InputProcesser::askMenuCommand()
		{
			do
			{
				std::cout << "Please, enter the command\nCommands:\n1) Weapons\n2) Armors\n3) Equipment \n4) Change weapon\n5) Change helmet\n6) Change cuirasse\n6) Current equipment\n6) Exit\n\n";
				MessageDisplayer::cmdLineBeggining();
				std::string command;
				std::getline(std::cin, command);
				
				if (command == "1" || command == "Weapons" || command == "weapons")
				{
					return common::Command::weapons;
				}
				else if (command == "2" || command == "Armors" || command == "armors")
				{
					return common::Command::armors;
				}
				else if (command == "3" || command == "Equipment" || command == "equipment")
				{
					return common::Command::equipment;
				}
				else if (command == "4" || command == "Change weapon" || command == "change weapon")
				{
					return common::Command::change_weapon;
				}
				else if (command == "5" || command == "Change helmet" || command == "change helmet")
				{
					return common::Command::change_helmet;
				}
				else if (command == "6" || command == "Change cuirasse" || command == "change cuirasse")
				{
					return common::Command::change_cuirasse;
				}
				else if (command == "6" || command == "Current equipment" || command == "current equipment")
				{
					return common::Command::current_equipment;
				}
				else if (command == "7" || command == "Exit" || command == "exit")
				{
					return common::Command::exit;
				}
				else
				{
					std::cout << "Unrecognized command entered.\n";
				}

			} while (true);
		}
	}
}
