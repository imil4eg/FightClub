#pragma once

#include "Characters/Character.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			class IBattle
			{
			public:
				virtual ~IBattle() noexcept = default;
				virtual void fightWithBot(characters::Character& player) = 0;
			};
		}
	}
}