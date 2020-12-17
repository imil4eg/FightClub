#pragma once

#include "Battle/HitDirection.h"

namespace fightclub
{
	namespace core
	{
		namespace io
		{
			class IInputProcesser
			{
			public:
				virtual ~IInputProcesser() = default;
				virtual battle::HitDirection getHitDirection() = 0;
			};
		}
	}
}
