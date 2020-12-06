#ifndef CONFIG_KEYS_H
#define CONFIG_KEYS_H

#include <string>

enum class ConfigKeys
{
	saveFile,
	max_config_keys
};

std::string toString(ConfigKeys configKey);

#endif // !CONFIG_KEYS_H

