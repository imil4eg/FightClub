#include <boost/lexical_cast.hpp>

#include "Battle/DamageCalculator.h"
#include "IO/MessageDisplayer.h"
#include "IO/InputProcesser.h"
#include "Characters/Player.h"

namespace fightclub
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

			io::MessageDisplayer::displayPlayerHit(damage, hitDirection);

			Character::hit(enemy, damage);

			io::MessageDisplayer::displayEnemyHP(enemy.getAttributes()->getHp());
		}
	}
}