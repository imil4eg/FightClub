#pragma once

#include <memory>

#include "Characters/Character.h"
#include "Battle/Fighters/Fighter.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			namespace fighters
			{
				class IFighterFactory
				{
				public:
					virtual ~IFighterFactory() = default;
					virtual std::unique_ptr<Fighter> create(characters::Character& character) const = 0;
				};
			}
		}
	}
}