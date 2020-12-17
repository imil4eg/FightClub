#pragma once

#include "Characters/Player.h"

namespace fightclub
{
	namespace characterstuff
	{
		class ICharacterCustomizeMenu
		{
		public:
			virtual ~ICharacterCustomizeMenu() = default;
			virtual void show(const characters::Player& player) = 0;
		};
	}
}
