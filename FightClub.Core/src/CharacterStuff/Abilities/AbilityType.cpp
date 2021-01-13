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
					case fightclub::core::characterstuff::abilities::AbilityType::boost:
						return "boost";
					case fightclub::core::characterstuff::abilities::AbilityType::attack:
						return "attack";
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