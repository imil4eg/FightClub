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
			auto player{ m_playerConfig->getCharacter() };
			m_battle->fightWithBot(*player);
			break;
		}
		case Command::customize_character:
			break;
		case Command::inventory:
			break;
		case Command::exit:
			auto& userData{ m_playerConfig->getUserModelData() };
			m_gameDataProcesser->save(userData);
			return;
		}
	}
}