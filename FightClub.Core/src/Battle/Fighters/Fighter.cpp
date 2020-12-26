#include "Battle/Fighters/Fighter.h"
#include "Battle/DamageCalculator.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			namespace fighters
			{
				struct Fighter::Impl
				{
					const io::IMessageDisplayer* m_messageDisplayer;
					const characters::Character* m_character;
					const std::string m_characterName;

					Impl(const io::IMessageDisplayer& messageDisplayer, const characters::Character& character, const std::string characterName) : 
						m_messageDisplayer{&messageDisplayer},
						m_character{ &character },
						m_characterName{ characterName }
					{
					}

					~Impl() = default;
				};

				Fighter::Fighter(const io::IMessageDisplayer& messageDisplayer, const characters::Character& character, const std::string characterName) :
					pImpl(std::make_unique<Impl>(messageDisplayer, character, characterName))
				{
				}

				Fighter::~Fighter() = default;

				const io::IMessageDisplayer& Fighter::getMessageDisplayer() const { return *pImpl->m_messageDisplayer; }
				const characters::Character& Fighter::getCharacter() const { return *pImpl->m_character; }
				const std::string& Fighter::getName() const { return pImpl->m_characterName; }

				void Fighter::hit(Fighter& target, battle::HitDirection hitDirection)
				{
					int damage = battle::DamageCalculator::Calculate(this->getCharacter(), target.getCharacter(), hitDirection);

					pImpl->m_messageDisplayer->display(pImpl->m_characterName + " hits " + target.getName() + " to " + hitDirection +
						" no " + std::to_string(damage) + " damage.\n");

					target.getCharacter().getAttributes()->setHp(target.getCharacter().getAttributes()->getHp() - damage);

					pImpl->m_messageDisplayer->display(pImpl->m_characterName + " HP: " + std::to_string(pImpl->m_character->getAttributes()->getHp()));
				}
			}
		}
	}
}