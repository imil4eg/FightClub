#pragma once

#include "Characters/Player.h"

namespace fightclub 
{
	namespace characterstuff 
	{
		class IInventoryManager
		{
		public:
			virtual ~IInventoryManager() = default;
			virtual void enterMenu(characters::Player& player) = 0;
		};
	}
}
