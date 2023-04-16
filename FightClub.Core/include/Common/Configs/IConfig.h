#pragma once

#include <string>

#include "Common/Configs/ConfigKeys.h"

namespace fightclub
{
	namespace core
	{
		namespace common
		{
			namespace configs
			{
				class IConfig
				{
				public:
					virtual ~IConfig() = default;

					virtual std::string get(ConfigKeys key) const = 0;
				};
			}
		}
	}
}