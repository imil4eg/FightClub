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
				void DynamicAbilitiesContainer::replace(int oldAbilitySlotNumber, const std::string& newAbilityName)
				{
					auto newAbilityIt{ AbilitiesContainer::get(newAbilityName) };

					auto& allAbilitiesContainer{ AbilitiesContainer::getAllAbilitiesForEditing() };
					if (newAbilityIt == allAbilitiesContainer.end())
					{
						throw exceptions::not_found_exception("Ability with name " + newAbilityName + " not found.");
					}

					auto& selectedAbilities{ AbilitiesContainer::getSelectedForEditing() };

					if ((oldAbilitySlotNumber - 1) < 0 || (oldAbilitySlotNumber - 1) > selectedAbilities.size())
					{
						throw std::out_of_range("Maximum size of abilities is " + std::to_string(selectedAbilities.size()) +
							". Entered " + std::to_string(oldAbilitySlotNumber) + " is out of range.\n");
					}

					if (selectedAbilities[oldAbilitySlotNumber - 1] != nullptr)
					{
						allAbilitiesContainer.push_back(selectedAbilities[oldAbilitySlotNumber - 1]);
					}

					selectedAbilities[(oldAbilitySlotNumber - 1)] = *newAbilityIt;
					allAbilitiesContainer.erase(newAbilityIt);
				}
			}
		}
	}
}