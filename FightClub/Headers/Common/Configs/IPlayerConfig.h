#ifndef I_PLAYER_CONFIG_H
#define I_PLAYER_CONFIG_H

#include "Characters/Character.h"
#include "Models/UserDataModel.h"


class IPlayerConfig
{
public:
	virtual ~IPlayerConfig() = default;
	virtual void initialize() = 0;
	virtual Character* getCharacter() = 0;
	virtual fightclub::models::UserDataModel& getUserModelData() = 0;
};


#endif // !I_PLAYER_CONFIG_H

