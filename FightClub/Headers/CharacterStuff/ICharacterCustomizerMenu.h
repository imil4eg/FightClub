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
			virtual void show(const core::characters::Player& player) = 0;
		};
	}
}
