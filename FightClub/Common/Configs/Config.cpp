#include <iostream>
#include <fstream>

#include "Common/Configs/Config.h"

std::string Config::get(ConfigKeys key) const
{
	std::ifstream configFile{ m_configPath };

	if (!configFile.good())
		return "";

	std::string wordToFind{toString(key)};

	std::string text;
	while (std::getline(configFile, text))
	{
		std::size_t found = text.find(m_delimeter);
		if (found != std::string::npos &&
			text.substr(0, found) == wordToFind)
		{
			return text.substr(found + 1, text.size() - found);
		}
	}

	return "";
}