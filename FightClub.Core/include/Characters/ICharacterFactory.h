#pragma once

#include <memory>

#include "Characters/Player.h"

namespace fightclub
{
	namespace core
	{
		namespace characters
		{
			class ICharacterFactory
			{
			public:
				virtual ~ICharacterFactory() noexcept = default;
				virtual std::unique_ptr<Player> createDefaultPlayer() = 0;
			};
		}
	}
}