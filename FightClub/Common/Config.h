#ifndef CONFIG_H
#define CONFIG_H

#include "IConfig.h"

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

	std::string get(ConfigKeys key) override;
};


#endif // !CONFIG_H

