#include <boost/algorithm/string.hpp>
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

				if (boost::iequals(input, "head"))
				{
					hitDirection = battle::HitDirection::head;
				}
				else if (boost::iequals(input, "body"))
				{
					hitDirection = battle::HitDirection::body;
				}
				else if (boost::iequals(input, "legs"))
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

				if (command == "1" || boost::iequals(command, "play"))
				{
					return common::Command::play;
				}
				else if (command == "2" || boost::iequals(command, "customize character"))
				{
					return common::Command::customize_character;
				}
				else if (command == "3" || boost::iequals(command, "inventory"))
				{
					return common::Command::inventory;
				}
				else if (command == "4" || boost::iequals(command, "exit"))
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
				std::cout << "Please, enter the command\nCommands:\n1) Weapons\n2) Armors\n3) Current equipment \n4) Change weapon\n5) Change helmet\n"
						     "6) Change cuirasse\n7) Change boots\n8) Exit\n\n";
				MessageDisplayer::cmdLineBeggining();
				std::string command;
				std::getline(std::cin, command);
				
				if (command == "1" || boost::iequals(command, "weapons"))
				{
					return common::Command::weapons;
				}
				else if (command == "2"  || boost::iequals(command, "armors"))
				{
					return common::Command::armors;
				}
				else if (command == "3" || boost::iequals(command, "equipment"))
				{
					return common::Command::equipment;
				}
				else if (command == "4" || boost::iequals(command, "change weapon"))
				{
					return common::Command::change_weapon;
				}
				else if (command == "5" || boost::iequals(command, "change helmet"))
				{
					return common::Command::change_helmet;
				}
				else if (command == "6" || boost::iequals(command, "change cuirasse"))
				{
					return common::Command::change_cuirasse;
				}
				else if (command == "7" || boost::iequals(command, "change boots"))
				{
					return common::Command::change_boots;
				}
				else if (command == "8" || boost::iequals(command, "exit"))
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
