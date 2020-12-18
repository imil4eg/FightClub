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
				void Fighter::hit(Fighter& target, battle::HitDirection hitDirection)
				{
					int damage = battle::DamageCalculator::Calculate(this->getCharacter(), target.getCharacter(), hitDirection);

					m_messageDisplayer->display(m_characterName + " hits " + target.getName() + hitDirection +
						" on " + std::to_string(damage) + " damage.\n");

					target.getCharacter().getAttributes()->setHp(target.getCharacter().getAttributes()->getHp() - damage);

					m_messageDisplayer->display(m_characterName + " HP: " + std::to_string(m_character->getAttributes()->getHp()));
				}
			}
		}
	}
}