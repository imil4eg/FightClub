#pragma once

#include <memory>

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
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				public:
					Config(const std::string& configPath); 
					~Config();

					std::string get(ConfigKeys key) const override;
				};
			}
		}
	}
}
