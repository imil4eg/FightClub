#include <iostream>

#include "CharacterStuff/AbilitiesDisplayer.h"

namespace fightclub
{
	namespace characterstuff
	{
		void AbilitiesDisplayer::showAll(const abils::AbilitiesContainer& container) const
		{
			std::cout << "\nAbilities:\n";

			const abils::AbilitiesContainer::abilities_t& allAbilities{ container.getAll() };
			show(allAbilities.begin(), allAbilities.end(), 
				[&](const abils::Ability* ability)
				{
					show(*ability);
				});
		}

		void AbilitiesDisplayer::showSelected(const abils::AbilitiesContainer& container) const
		{
			std::cout << "\nCurrent selected abilities:\n";

			const abils::AbilitiesContainer::selectedAbilities_t& selectedAbilities{ container.getSelected() };
			show(selectedAbilities.begin(), selectedAbilities.end(),
				[&](const abils::Ability* ability)
				{
					if (ability == nullptr)
					{
						std::cout << "Empty slot";
					}
					else
					{
						show(*ability);
					}
				});
		}

		void AbilitiesDisplayer::show(const abils::Ability& ability) const
		{
			std::cout << "Name: " + ability.getName() + " Type: " + abils::to_string(ability.getType()) +
				" Cost: " + std::to_string(ability.getCost()) + " Value: " + std::to_string(ability.getValue()) + 
				" Duration: " + std::to_string(ability.getDuration());
		}

		template<class It>
		void AbilitiesDisplayer::show(It begin, const It end, std::function<void(const abils::Ability*)> displayAbility) const
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