#include <iostream>

#include "Menu.h"
#include "Characters/Player.h"
#include "IO/InputProcesser.h"

void Menu::show() const 
{
	std::cout << "Welcome to the fight club, buddy!\n";
	while (true)
	{
		switch (InputProcesser::askCommand())
		{
		case Command::play:
		{
			Player player{ new Attributes{100, 1, 1, 1}, new Equipment{}, CharacterType::strong, new Weapon{10} };
			m_battle->fightWithBot(player);
			break;
		}
		case Command::customize_character:
			break;
		case Command::inventory:
			break;
		case Command::exit:
			return;
		}
	}
}