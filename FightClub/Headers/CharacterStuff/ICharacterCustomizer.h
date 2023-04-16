#pragma once

#include "CharacterStuff/Attributes.h"

namespace fightclub
{
	namespace characterstuff
	{
		class ICharacterCustomizer
		{
		public:
			virtual void changeAttributes(
				core::characterstuff::Attributes& attributes) = 0;
		};
	}
}
