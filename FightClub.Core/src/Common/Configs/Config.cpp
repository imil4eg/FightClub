#include <fstream>

#include "Common/Configs/Config.h"

namespace fightclub
{
	namespace core
	{
		namespace common
		{
			namespace configs
			{
				struct Config::Impl
				{
					const std::string m_delimeter = "=";
					const std::string m_configPath;

					Impl(const std::string& configPath) :
						m_configPath{ configPath }
					{
					}
					
					~Impl() = default;
				};

				Config::Config(const std::string& configPath) :
					pImpl(std::make_unique<Impl>(configPath))
				{
				}

				Config::~Config() = default;

				std::string Config::get(ConfigKeys key) const
				{
					std::ifstream configFile{ pImpl->m_configPath };

					if (!configFile.good())
						return "";

					std::string wordToFind{ toString(key) };

					std::string text;
					while (std::getline(configFile, text))
					{
						std::size_t found = text.find(pImpl->m_delimeter);
						if (found != std::string::npos &&
							text.substr(0, found) == wordToFind)
						{
							return text.substr(found + 1, text.size() - found);
						}
					}

					return "";
				}
			}
		}
	}
}