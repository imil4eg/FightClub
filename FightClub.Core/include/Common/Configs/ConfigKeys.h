#pragma once

#include <string>

namespace fightclub
{
	namespace core
	{
		namespace common
		{
			namespace configs
			{
				enum class ConfigKeys
				{
					saveFile,
					weaponsFile,
					armorsFile,
					abilitiesFile,
					max_config_keys
				};

				std::string toString(ConfigKeys configKey);
			}
		}
	}
}