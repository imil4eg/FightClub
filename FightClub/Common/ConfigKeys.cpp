#include <exception>

#include "ConfigKeys.h"

std::string toString(ConfigKeys configKey)
{
	std::string result;

	switch (configKey)
	{
	case ConfigKeys::saveFile:
		result = "SaveFileDirectory";
	default:
		throw std::exception("Specified config key not found.");
	}

	return result;
}