#include <boost/algorithm/string.hpp>

#include "CharacterStuff/AbilitiesManager.h"
#include "CharacterStuff/Abilities/DynamicAbilitiesContainer.h"
#include "Common/IntHelper.h"
#include "Exceptions/invalid_input_type.h"

namespace fightclub
{
	namespace characterstuff
	{
		void AbilitiesManager::enter(core::characters::Character& character)
		{
			while (true)
			{
				std::cout << "\nPlease, enter the command\nCommands:\n1) " << m_allAbilitiesCommand
					<< "\n2) " << m_selectedAbilitiesCommand
					<< "\n3) " << m_editAbilitiesCommand
					<< "\n4) " << m_exitCommand << '\n';

				std::string command{ m_inputProcesser->getLine() };

				if (boost::iequals(command, m_allAbilitiesCommand))
				{
					m_abilitiesDisplayer->showAll(character.getAbilitiesContainer());
				}
				else if (boost::iequals(command, m_selectedAbilitiesCommand))
				{
					m_abilitiesDisplayer->showSelected(character.getAbilitiesContainer());
				}
				else if (boost::iequals(command, m_editAbilitiesCommand))
				{
					changeSelectedAbilities(character.getAbilitiesContainer());
				}
				else if (boost::iequals(command, m_exitCommand))
				{
					return;
				}
				else
				{
					std::cout << "\n\nEntered unrecognized command.\n\n";
				}
			}
		}

		void AbilitiesManager::changeSelectedAbilities(abils::AbilitiesContainer& container) const
		{
			while (true)
			{
				try
				{

					m_abilitiesDisplayer->showAll(container);

					std::cout << '\n';

					m_abilitiesDisplayer->showSelected(container);

					std::cout << "\nEnter ability to change slot number or " <<  m_exitCommand << " to leave\n";
					std::string oldAbilityName{ m_inputProcesser->getLine() };

					if (boost::iequals(oldAbilityName, m_exitCommand))
					{
						return;
					}

					int oldAbilitySlotNumber{};
					if (!common::IntHelper::tryParse(oldAbilityName, oldAbilitySlotNumber))
					{
						throw exceptions::invalid_input_type("The input " + oldAbilityName + " is of incorrect type.");
					}

					std::cout << "\nEnter new ability name\n";
					std::string newAbilityName{ m_inputProcesser->getLine() };

					auto dynamicContainer{ dynamic_cast<abils::DynamicAbilitiesContainer*>(&container) };

					dynamicContainer->replace(oldAbilitySlotNumber, newAbilityName);
				}
				catch (std::exception& ex)
				{
					std::cout << ex.what() << '\n';
				}
			}
		}
	}
}