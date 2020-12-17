#include "Battle/DamageCalculator.h"
#include "Characters/Player.h"

namespace fightclub
{
	namespace core
	{
		namespace characters
		{
			void Player::playTurn(characters::Character& target)
			{
				io::MessageDisplayer::displayPlayerTurn();

				auto hitDirection{ io::InputProcesser::askHitDirection() };

				this->hit(target, hitDirection);
			}

			void Player::hit(Character& enemy, battle::HitDirection hitDirection)
			{
				int damage = battle::DamageCalculator::Calculate(*this, enemy, hitDirection);

				Character::hit(enemy, damage);
			}
		}
	}
}