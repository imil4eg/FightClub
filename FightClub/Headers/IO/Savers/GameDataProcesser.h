#ifndef GAME_SAVER_H
#define GAME_SAVER_H

#include <memory>

#include "Models/UserDataModel.h"
#include "../../Characters/Character.h"

class GameDataProcesser
{
public:
	virtual ~GameDataProcesser() = default;
	virtual std::unique_ptr<fightclub::models::UserDataModel> load() = 0;
	virtual void save(fightclub::models::UserDataModel& userDataModel) const = 0;
};


#endif // !GAME_SAVER_H

