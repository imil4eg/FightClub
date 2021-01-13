#pragma once

#include <array>
#include <boost/uuid/uuid.hpp>
#include <memory>

#include "AbilitiesContainer.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace abilities
			{
				class DynamicAbilitiesContainer : public AbilitiesContainer
				{
				public:
					DynamicAbilitiesContainer(std::vector<std::unique_ptr<Ability>>&& abilities,
						selectedAbilityIds_t& selectedAbilityIds) :
						AbilitiesContainer(std::move(abilities), selectedAbilityIds)
					{
					}

					DynamicAbilitiesContainer() :
						AbilitiesContainer()
					{
					}

					void replace(int oldAbilitySlotNumber, const std::string& newAbilityName);
				};
			}
		}
	}
}