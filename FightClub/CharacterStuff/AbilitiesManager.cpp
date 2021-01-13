#include <boost/algorithm/string.hpp>

#include "CharacterStuff/AbilitiesManager.h"
#include "CharacterStuff/Abilities/DynamicAbilitiesContainer.h"
#include "Common\IntHelper.h"
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
					displayAllAbilities(character.getAbilitiesContainer().getAll());
				}
				else if (boost::iequals(command, m_selectedAbilitiesCommand))
				{
					displaySelectedAbilities(character.getAbilitiesContainer().getSelected());
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
					displayAllAbilities(container.getAll());

					std::cout << '\n';

					displaySelectedAbilities(container.getSelected());

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

		void AbilitiesManager::displayAllAbilities(const abils::AbilitiesContainer::abilities_t& abilities) const
		{
			std::cout << "\nAbilities:\n";

			displayAbilities<abils::AbilitiesContainer::abilities_t::const_iterator>(abilities.cbegin(), abilities.cend(),
				[&](const abils::Ability* ability)
				{
					displayAbility(*ability);
				});
		}

		void AbilitiesManager::displaySelectedAbilities(const abils::AbilitiesContainer::selectedAbilities_t& selectedAbilities) const
		{
			std::cout << "\nCurrent selected abilities:\n";

			displayAbilities<abils::AbilitiesContainer::selectedAbilities_t::const_iterator>(selectedAbilities.cbegin(), selectedAbilities.cend(),
				[&](const abils::Ability* ability)
				{
					if (ability == nullptr)
						std::cout << "Empty slot";
					else
						displayAbility(*ability);
				});
		}

		void AbilitiesManager::displayAbility(const abils::Ability& ability) const
		{
			std::cout << "Name: " + ability.getName() + " Type: " + abils::to_string(ability.getType()) +
				" Cost: " + std::to_string(ability.getCost()) + " Damage: " + std::to_string(ability.getDamage());
		}


		template<class It>
		void AbilitiesManager::displayAbilities(It begin, const It end, std::function<void(const abils::Ability*)> displayAbility) const
		{			
			int index{ 1 };
			while (begin != end)
			{
				std::cout << index << ") ";

				displayAbility(*begin);

				std::cout << '\n';

				++begin;
				++index;
			}
		}
	}
}