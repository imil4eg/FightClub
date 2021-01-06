#pragma once

#include "Characters/Character.h"
#include "CharacterStuff/BodyPart.h"
#include "IO/IMessageDisplayer.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			namespace fighters
			{
				class Fighter
				{
				private:
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				protected:
					Fighter(const io::IMessageDisplayer& messageDisplayer, const characters::Character& character, const std::string characterName);

					const io::IMessageDisplayer& getMessageDisplayer() const;
					void setProtectingPart(characterstuff::BodyPart bodyPart);
					void setHitDirection(characterstuff::BodyPart hitDirection);

				public:
					virtual ~Fighter();
					virtual void askDecisions() = 0;
					void playTurn(Fighter& target);
				};
			}
		}
	}
}