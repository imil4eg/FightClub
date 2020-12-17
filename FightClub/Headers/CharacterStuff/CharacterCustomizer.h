#pragma once

#include "ICharacterCustomizer.h"

namespace fightclub
{
	namespace characterstuff
	{
		class CharacterCustomizer : public ICharacterCustomizer
		{
		private:
			const int m_attributePerLevel{10};

		public:
			void changeAttributes(Attributes& attributes) override;
		};
	}
}