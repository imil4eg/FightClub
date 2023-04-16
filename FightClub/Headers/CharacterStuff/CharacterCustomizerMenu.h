#pragma once

#include <string>

#include "ICharacterCustomizerMenu.h"

namespace fightclub
{
	namespace characterstuff
	{
		class CharacterCustomizerMenu : public ICharacterCustomizeMenu
		{
		private:
			const std::string m_currentAttributesText{ "Current attributes" };
			const std::string m_changeAttributesText{ "Change attributes" };
			const std::string m_exitText{ "Exit" };

		public:
			void show(const core::characters::Player& player) override;
		};
	}
}