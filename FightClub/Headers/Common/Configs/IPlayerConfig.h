#ifndef I_PLAYER_CONFIG_H
#define I_PLAYER_CONFIG_H

#include "../../Characters/Character.h"

class IPlayerConfig
{
public:
	virtual ~IPlayerConfig() = default;
	virtual Character* getCharacter() = 0;
	virtual void initialize() = 0;
};


#endif // !I_PLAYER_CONFIG_H

