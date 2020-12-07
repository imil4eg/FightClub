#include <exception>

#include "ConfigKeys.h"

std::string toString(ConfigKeys configKey)
{
	switch (configKey)
	{
	case ConfigKeys::saveFile:
		return "SaveFileDirectory";
	default:
		throw std::exception("Specified config key not found.");
	}
}