#include <boost/algorithm/string.hpp>
#include <iostream>

#include "CharacterStuff/CharacterCustomizerMenu.h"
#include "IO/MessageDisplayer.h"

namespace fightclub
{
	namespace characterstuff
	{
		void CharacterCustomizerMenu::show(const core::characters::Player& player)
		{
			while (true)
			{
				std::cout << "\nSelect the command:\n1) " << m_currentAttributesText << "\n2) " << m_changeAttributesText << "\n3) " << m_exitText << '\n';
				io::MessageDisplayer::cmdLineBeggining();
				
				std::string command{};
				std::getline(std::cin, command);

				if (boost::iequals(command, m_currentAttributesText))
				{
					std::cout << player.getAttributes() << '\n';
				}
				else if (boost::iequals(command, m_changeAttributesText))
				{

				}
				else if (boost::iequals(command, m_exitText))
				{
					return;
				}

				std::cout << '\n';
			}
		}
	}
}