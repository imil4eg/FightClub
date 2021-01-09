#include "CharacterStuff/Abilities/DynamicAbilitiesContainer.h"
#include "Exceptions/not_found_exception.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace abilities
			{
				void DynamicAbilitiesContainer::replace(const std::string& oldAbilityName, const std::string& newAbilityName)
				{
					auto newAbilityIt{ AbilitiesContainer::get(newAbilityName) };

					if (newAbilityIt == AbilitiesContainer::getAll().end())
					{
						throw exceptions::not_found_exception("Ability with name " + newAbilityName + " not found.");
					}

					auto& selectedAbilities{ AbilitiesContainer::getSelected() };

					auto oldSelectedAbilityIt{ std::find_if(selectedAbilities.begin(), selectedAbilities.end(),
						[&](const Ability* ability)
						{
							return ability->getName() == oldAbilityName;
						}) };

					if (oldSelectedAbilityIt == selectedAbilities.end())
					{
						throw exceptions::not_found_exception("Ability with name " + oldAbilityName + " not found.");
					}

					*oldSelectedAbilityIt = *newAbilityIt;
				}
			}
		}
	}
}