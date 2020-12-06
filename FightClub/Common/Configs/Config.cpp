#include <iostream>
#include <fstream>

#include "Config.h"

std::string Config::get(ConfigKeys key)
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
			return text.substr(found, text.size() - found);
		}
	}

	return "";
}