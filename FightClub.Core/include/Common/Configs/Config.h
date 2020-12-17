#pragma once

#include "IConfig.h"

namespace fightclub
{
	namespace core
	{
		namespace common
		{
			namespace configs
			{
				class Config : public IConfig
				{
				private:
					const std::string m_delimeter = "=";
					const std::string m_configPath;

				public:
					Config(const std::string& configPath) :
						m_configPath{ configPath }
					{
					}

					std::string get(ConfigKeys key) const override;
				};
			}
		}
	}
}
