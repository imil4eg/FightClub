#ifndef I_CHARACTER_FACTORY_H
#define I_CHARACTER_FACTORY_H

#include <string>

#include "Player.h"

namespace fightclub
{
	namespace characters
	{
		class ICharacterFactory
		{
		public:
			virtual ~ICharacterFactory() noexcept = default;
			virtual std::unique_ptr<Player> createDefaultPlayer() = 0;
		};
	}
}

#endif // !I_CHARACTER_FACTORY_H

