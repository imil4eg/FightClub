#pragma once

#include <string>
#include <functional>

#include "CharacterStuff/Abilities/IAbilitiesManager.h"
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

		public:
			AbilitiesManager(core::io::IInputProcesser& inputProcesser) :
				m_inputProcesser{ &inputProcesser }
			{
			}

			void enter(core::characters::Character& character) override;
			void changeSelectedAbilities(abils::AbilitiesContainer& container) const override;
			void displayAllAbilities(const abils::AbilitiesContainer::abilities_t& abilities) const override;
			void displaySelectedAbilities(const abils::AbilitiesContainer::selectedAbilities_t& selectedAbilities) const override;
			void displayAbility(const abils::Ability& ability) const override;

		private:
			template<class It>
			void displayAbilities(It begin, const It end, std::function<void(const abils::Ability*)> predicate) const;
		};
	}
}