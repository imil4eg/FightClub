#include <boost/algorithm/string.hpp>
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
			std::cout << "Please, enter the command\nCommands:\n1) Play\n2) Customize character\n3) Inventory\n4) Exit\n\n";
			auto commandStr{ m_inputProcesser->getLine() };

			if (boost::iequals(commandStr, "play"))
			{
				auto player{ m_playerConfig->getCharacter() };
				m_battle->fightWithBot(player);
			}
			else if (boost::iequals(commandStr, "customize character"))
			{

			}
			else if (boost::iequals(commandStr, "inventory"))
			{

			}
			else if (boost::iequals(commandStr, "exit"))
			{
				m_gameDataProcesser->save(*(m_playerConfig->getCharacter()));
				return;
			}
		}
	}
}