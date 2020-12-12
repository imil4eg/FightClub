#ifndef IBATTLE_H
#define IBATTLE_H

#include "../Characters/Character.h"

namespace fightclub
{
	namespace battle
	{
		class IBattle
		{
		public:
			virtual ~IBattle() noexcept = default;
			virtual void fightWithBot(characters::Character& player) = 0;
		};
	}
}

#endif // !IBATTLE_H


