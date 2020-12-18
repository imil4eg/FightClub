#pragma once

#include "Characters/Character.h"
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
					const io::IMessageDisplayer* m_messageDisplayer;
					const characters::Character* m_character;
					const std::string m_characterName;

				protected:
					Fighter(io::IMessageDisplayer& messageDisplayer, characters::Character& character, std::string characterName) :
						m_messageDisplayer{ &messageDisplayer },
						m_character{ &character },
						m_characterName{ characterName }
					{
					}

					const io::IMessageDisplayer& getMessageDisplayer() const { return *m_messageDisplayer; }
					const characters::Character& getCharacter() const { return *m_character; }
					const std::string& getName() const { return m_characterName; }

				public:
					virtual ~Fighter() = default;
					virtual void playTurn(Fighter& target) = 0;
					void hit(Fighter& target, battle::HitDirection hitDirection);
				};
			}
		}
	}
}