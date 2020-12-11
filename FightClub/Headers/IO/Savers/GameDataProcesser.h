#ifndef GAME_SAVER_H
#define GAME_SAVER_H

#include <memory>

#include "Characters/Player.h"

class GameDataProcesser
{
public:
	virtual ~GameDataProcesser() = default;
	virtual std::unique_ptr<Player> load() = 0;
	virtual void save(Player& player) const = 0;
};


#endif // !GAME_SAVER_H

