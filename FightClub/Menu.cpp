#include "Menu.h"

#include <boost/algorithm/string.hpp>
#include <iostream>

#include "Characters/Player.h"
#include "IO/InputProcesser.h"

namespace fightclub
{
	void Menu::show() const
	{
		std::cout << "Welcome to the fight club, buddy!\n";

		auto* player{ m_playerConfig->getCharacter() };
		while (true)
		{
			std::cout << "Please, enter the command\nCommands:\n1) Play\n2) Customize character\n3) Inventory\n4) Abilities\n5) Exit\n\n";
			auto commandStr{ m_inputProcesser->getLine() };

			if (boost::iequals(commandStr, "play"))
			{
				m_battle->fightWithBot(*player);
			}
			else if (boost::iequals(commandStr, "customize character"))
			{
				m_attributesManger->enterAttributesManager(*player);
			}
			else if (boost::iequals(commandStr, "inventory"))
			{
				m_inventoryManager->enterInventory(*player);
			}
			else if (boost::iequals(commandStr, "abilities"))
			{
				m_abilitiesManager->enter(*player);
			}
			else if (boost::iequals(commandStr, "exit"))
			{
				m_gameDataProcesser->save(*player);
				return;
			}
		}
	}
}