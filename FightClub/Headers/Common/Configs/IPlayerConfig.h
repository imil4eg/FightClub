#ifndef I_PLAYER_CONFIG_H
#define I_PLAYER_CONFIG_H

#include "Characters/Player.h"

namespace fightclub
{
	namespace common
	{
		namespace configs
		{
			class IPlayerConfig
			{
			public:
				virtual ~IPlayerConfig() = default;
				virtual void initialize() = 0;
				virtual characters::Player* getCharacter() = 0;
			};
		}
	}
}

#endif // !I_PLAYER_CONFIG_H

	