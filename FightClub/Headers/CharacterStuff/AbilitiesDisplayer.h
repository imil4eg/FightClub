#pragma once

#include <functional>

#include "CharacterStuff/Abilities/IAbilitiesDisplayer.h"

namespace fightclub
{
	namespace characterstuff
	{
		namespace abils = core::characterstuff::abilities;

		class AbilitiesDisplayer : public abils::IAbilitiesDisplayer
		{
		public:
			void showAll(const abils::AbilitiesContainer& container) const override;
			void showSelected(const abils::AbilitiesContainer& container) const override;
			void show(const abils::Ability& ability) const override;

		private:
			template<class It>
			void show(It begin, const It end, std::function<void(const abils::Ability*)> displayAbility) const;
		};
	}
}