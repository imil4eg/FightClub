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
					const characters::Character& getCharacter() const;
					const std::string& getName() const;

				public:
					virtual ~Fighter();
					virtual void playTurn(Fighter& target) = 0;
					void hit(Fighter& target, characterstuff::BodyPart hitDirection);
				};
			}
		}
	}
}