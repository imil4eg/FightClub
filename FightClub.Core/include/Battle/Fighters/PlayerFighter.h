#pragma once

#include "Fighter.h"
#include "CharacterStuff/Abilities/Ability.h"
#include "CharacterStuff/Abilities/IAbilitiesDisplayer.h"
#include "IO/IInputProcesser.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			namespace fighters
			{
				namespace abils = characterstuff::abilities;

				class PlayerFighter : public Fighter
				{
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				public:
					PlayerFighter(const io::IMessageDisplayer& messageDisplayer, 
								  const io::IInputProcesser& inputProcesser, 
								  const abils::IAbilitiesDisplayer& abilityDisplayer,
								  characters::Character& player);
					~PlayerFighter();

					void askDecisions() override;
				};
			}
		}
	}
}