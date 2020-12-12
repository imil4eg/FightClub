#ifndef GAME_SAVER_H
#define GAME_SAVER_H

#include <memory>

#include "Characters/Player.h"

namespace fightclub
{
	namespace io
	{
		namespace savers
		{
			class GameDataProcesser
			{
			public:
				virtual ~GameDataProcesser() = default;
				virtual std::unique_ptr<characters::Player> load() = 0;
				virtual void save(characters::Player& player) const = 0;
			};
		}
	}
}

#endif // !GAME_SAVER_H

