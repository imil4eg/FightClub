#include <exception>

#include "ConfigKeys.h"

std::string toString(ConfigKeys configKey)
{
	switch (configKey)
	{
	case ConfigKeys::saveFile:
		return "SaveFileDirectory";
	case ConfigKeys::weaponsFile:
		return "WeaponsFileDirectory";
	case ConfigKeys::armorsFile:
		return "ArmorsFileDirectory";
	default:
		throw std::exception("Specified config key not found.");
	}
}