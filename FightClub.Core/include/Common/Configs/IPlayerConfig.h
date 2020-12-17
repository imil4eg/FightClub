#pragma once

#include "Characters/Player.h"

namespace fightclub
{
	namespace core
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
}