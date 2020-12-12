#ifndef I_CONFIG_H
#define I_CONFIG_H

#include <string>

#include "ConfigKeys.h"

namespace fightclub
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

#endif // !I_CONFIG_H

