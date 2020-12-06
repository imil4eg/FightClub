#ifndef I_CONFIG_H
#define I_CONFIG_H

#include <string>

#include "ConfigKeys.h"

class IConfig
{
public:
	virtual ~IConfig() = default;

	virtual std::string get(ConfigKeys key) = 0;
};

#endif // !I_CONFIG_H

