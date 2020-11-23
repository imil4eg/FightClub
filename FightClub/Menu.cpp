#include <iostream>

#include "Menu.h"

void Menu::show() const 
{
	std::cout << "Welcom to the fight club, buddy!\n";

	bool isExistCommand = false;
	do
	{
		std::cout << "Please, enter the command\nCommands:\n1) Play\n2) Customize character\n3) Inventory\n4) Exit\n\n";
		std::cout << "FightClub>";
		std::string command;
		std::cin >> command;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (command == "1" || command == "Play" || command == "play")
		{

		}
		else if (command == "2" || command == "Customize character" || command == "customize character")
		{

		}
		else if (command == "3" || command == "Invetory" || command == "inventory")
		{

		}
		else if (command == "4" || command == "Exit" || command == "exit")
		{
			isExistCommand = true;
		}
		else
		{
			std::cout << "Unrecognized command entered.\n";
		}

	} while (!isExistCommand);
}