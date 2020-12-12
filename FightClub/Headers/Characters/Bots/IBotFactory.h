#ifndef IBOT_FACTORY_H
#define IBOT_FACTORY_H

#include "Bot.h"
#include "../Character.h"

namespace fightclub
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

#endif // !BOT_FACTORY_H

