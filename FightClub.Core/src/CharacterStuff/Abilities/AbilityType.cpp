#include <stdexcept>

#include "CharacterStuff/Abilities/AbilityType.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace abilities
			{
				std::string to_string(AbilityType type)
				{
					switch (type)
					{
					case fightclub::core::characterstuff::abilities::AbilityType::damage_boost:
						return "damage boost";
					case fightclub::core::characterstuff::abilities::AbilityType::armor_boost:
						return "armor boost";
					case fightclub::core::characterstuff::abilities::AbilityType::trap:
						return "trap";
					default:
						throw std::out_of_range("Specified " + std::to_string(static_cast<int>(type)) + " does not exist.");
					}
				}
			}
		}
	}
}