#include <iostream>

#include "MessageDisplayer.h"
#include "InputProcesser.h"

HitDirection InputProcesser::askHitDirection()
{
	HitDirection hitDirection{};
	do
	{
		std::cout << "Choose where will you hit the opponen:\n1) Head\n2) Body\n3) Legs\n";
		MessageDisplayer::cmdLineBeggining();
		std::string input;
		std::cin >> input;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (input == "Head")
		{
			hitDirection = HitDirection::head;
		}
		else if (input == "Body")
		{
			hitDirection = HitDirection::body;
		}
		else if (input == "Legs")
		{
			hitDirection = HitDirection::legs;
		}
		else
		{
			hitDirection = HitDirection::max_hit_direction;
		}

	} while (hitDirection == HitDirection::max_hit_direction);

	return static_cast<HitDirection>(hitDirection);
}

Command InputProcesser::askCommand()
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
			return Command::play;
		}
		else if (command == "2" || command == "Customize character" || command == "customize character")
		{
			return Command::customize_character;
		}
		else if (command == "3" || command == "Invetory" || command == "inventory")
		{
			return Command::inventory;
		}
		else if (command == "4" || command == "Exit" || command == "exit")
		{
			return Command::exit;
		}
		else
		{
			std::cout << "Unrecognized command entered.\n";
		}

	} while (true);
}