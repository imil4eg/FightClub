#include "Battle/Fighters/Fighter.h"
#include "Battle/DamageCalculator.h"
#include "CharacterStuff/BodyPart.h"

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
					characterstuff::BodyPart m_protectingPart;
					characterstuff::BodyPart m_hitDirection;

					Impl(const io::IMessageDisplayer& messageDisplayer, const characters::Character& character, const std::string characterName) : 
						m_messageDisplayer{&messageDisplayer},
						m_character{ &character },
						m_characterName{ characterName },
						m_protectingPart{characterstuff::BodyPart::max_body_part},
						m_hitDirection{characterstuff::BodyPart::max_body_part}
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
				void Fighter::setProtectingPart(characterstuff::BodyPart bodyPart) { pImpl->m_protectingPart = bodyPart; }
				void Fighter::setHitDirection(characterstuff::BodyPart hitDirection) { pImpl->m_hitDirection = hitDirection; }

				void Fighter::playTurn(Fighter& target)
				{
					int damage = battle::DamageCalculator::Calculate(*this->pImpl->m_character, *target.pImpl->m_character, 
																	 pImpl->m_hitDirection, target.pImpl->m_protectingPart);

					pImpl->m_messageDisplayer->display(pImpl->m_characterName + " hits " + target.pImpl->m_characterName + " to " + pImpl->m_hitDirection +
						" no " + std::to_string(damage) + " damage.\n");

					target.pImpl->m_character->getAttributes()->setHp(target.pImpl->m_character->getAttributes()->getHp() - damage);

					pImpl->m_messageDisplayer->display(target.pImpl->m_characterName + " HP: " +
						std::to_string(target.pImpl->m_character->getAttributes()->getHp()));
				}
			}
		}
	}
}