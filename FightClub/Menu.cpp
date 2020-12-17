#include <iostream>

#include "Menu.h"
#include "Characters/Player.h"
#include "IO/InputProcesser.h"

namespace fightclub
{
	void Menu::show() const
	{
		std::cout << "Welcome to the fight club, buddy!\n";
		while (true)
		{
			switch (io::InputProcesser::askCommand())
			{
			case common::Command::play:
			{
				auto player{ m_playerConfig->getCharacter() };
				m_battle->fightWithBot(*player);
				break;
			}
			case common::Command::customize_character:
				break;
			case common::Command::inventory:
				m_inventoryManager->enterMenu(*m_playerConfig->getCharacter());
				break;
			case common::Command::exit:
				m_gameDataProcesser->save(*(m_playerConfig->getCharacter()));
				return;
			}
		}
	}
}