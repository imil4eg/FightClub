#pragma once

#include <memory>

#include "Characters/Player.h"

namespace fightclub
{
	namespace core
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
}