#ifndef GAME_SAVER_H
#define GAME_SAVER_H

#include "../../Characters/Character.h"

class GameDataProcesser
{
public:
	virtual ~GameDataProcesser() = default;
	virtual Character* load() = 0;
	virtual void save(Character& character) const = 0;
};


#endif // !GAME_SAVER_H

