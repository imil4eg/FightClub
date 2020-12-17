#pragma once

#include "Bot.h"

namespace fightclub
{
	namespace core
	{
		namespace characters
		{
			namespace bots
			{
				class IBotFactory
				{
				public:
					virtual ~IBotFactory() noexcept = default;
					virtual Bot create(const Character& player) = 0;
				};
			}
		}
	}
}