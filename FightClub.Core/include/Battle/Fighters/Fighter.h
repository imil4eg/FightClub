#pragma once

#include "Characters/Character.h"
#include "CharacterStuff/BodyPart.h"
#include "CharacterStuff/Abilities/Ability.h"
#include "IO/IMessageDisplayer.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			namespace fighters
			{
				namespace abils = characterstuff::abilities;

				class Fighter
				{
				public:
					typedef std::pair<const abils::Ability*, int> buffWithDuration_t;
					
				private:
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				protected:
					Fighter(const io::IMessageDisplayer& messageDisplayer, const characters::Character& character, const std::string characterName);

					const io::IMessageDisplayer& getMessageDisplayer() const;
					const characters::Character& getCharacter() const;
					const std::vector<buffWithDuration_t>& getBuffs() const;
					int getLeftStamina() const;
					void setProtectingPart(characterstuff::BodyPart bodyPart);
					void setHitDirection(characterstuff::BodyPart hitDirection);
					void setUsedSpell(const abils::Ability* ability);

				public:
					virtual ~Fighter();
					
					bool isDead();

					virtual void askDecisions() = 0;
					void playTurn(Fighter& target);
				};
			}
		}
	}
}