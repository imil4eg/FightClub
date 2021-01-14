#pragma once

#include <string>
#include <functional>

#include "CharacterStuff/Abilities/IAbilitiesManager.h"
#include "CharacterStuff/Abilities/IAbilitiesDisplayer.h"
#include "IO/IInputProcesser.h"

namespace fightclub
{
	namespace characterstuff
	{
		namespace abils = fightclub::core::characterstuff::abilities;

		class AbilitiesManager : public core::characterstuff::abilities::IAbilitiesManager
		{
		private:
			const std::string m_selectedAbilitiesCommand{ "Selected abilities" };
			const std::string m_allAbilitiesCommand{ "All abilities" };
			const std::string m_editAbilitiesCommand{ "Edit abilities" };
			const std::string m_exitCommand{ "Exit" };

			core::io::IInputProcesser* m_inputProcesser;
			abils::IAbilitiesDisplayer* m_abilitiesDisplayer;

		public:
			AbilitiesManager(core::io::IInputProcesser& inputProcesser, abils::IAbilitiesDisplayer& abilitiesDisplayer) :
				m_inputProcesser{ &inputProcesser },
				m_abilitiesDisplayer{&abilitiesDisplayer}
			{
			}

			void enter(core::characters::Character& character) override;
			void changeSelectedAbilities(abils::AbilitiesContainer& container) const override;
		};
	}
}