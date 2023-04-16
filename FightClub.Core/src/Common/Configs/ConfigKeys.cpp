#include <stdexcept>

#include "Common/Configs/ConfigKeys.h"

namespace fightclub
{
	namespace core
	{
		namespace common
		{
			namespace configs
			{
				std::string toString(ConfigKeys configKey)
				{
					switch (configKey)
					{
					case ConfigKeys::saveFile:
						return "SaveFileDirectory";
					case ConfigKeys::weaponsFile:
						return "WeaponsFileDirectory";
					case ConfigKeys::armorsFile:
						return "ArmorsFileDirectory";
					case ConfigKeys::abilitiesFile:
						return "AbilitiesFileDirectory";
					default:
						throw std::runtime_error("Specified config key not found.");
					}
				}
			}
		}
	}
}