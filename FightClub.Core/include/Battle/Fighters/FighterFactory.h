#pragma once

#include "BotFighter.h"
#include "Characters/Player.h"
#include "CharacterStuff/Abilities/IAbilitiesDisplayer.h"
#include "PlayerFighter.h"
#include "IO/IMessageDisplayer.h"
#include "IO/IInputProcesser.h"
#include "IFighterFactory.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			namespace fighters
			{
				class FighterFactory : public IFighterFactory
				{
				private:
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				public:
					FighterFactory(const io::IMessageDisplayer& messageDisplayer, const io::IInputProcesser& inputProcesser, 
						const characterstuff::abilities::IAbilitiesDisplayer& abilityDisplayer);
					~FighterFactory();

					std::unique_ptr<Fighter> create(characters::Character& character) const override;
				};
			}
		}
	}
}