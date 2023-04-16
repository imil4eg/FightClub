#pragma once

#include <array>
#include <boost/uuid/uuid.hpp>
#include <string>
#include <vector>
#include <memory>

#include "Ability.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace abilities
			{
				class AbilitiesContainer
				{
				public:
					typedef std::array<boost::uuids::uuid, 3> selectedAbilityIds_t;
					typedef std::vector<Ability*> abilities_t;
					typedef std::array<Ability*, 3> selectedAbilities_t;

				private:
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				protected:
					abilities_t::iterator get(const std::string& abilityName) const;
					selectedAbilities_t& getSelectedForEditing();
					abilities_t& getAllAbilitiesForEditing();

				public:
					AbilitiesContainer(std::vector<std::unique_ptr<Ability>>&& abilities, 
									   selectedAbilityIds_t& selectedAbilityIds);
					AbilitiesContainer();

					virtual ~AbilitiesContainer();

					const abilities_t& getAll() const;
					const selectedAbilities_t& getSelected() const;
					selectedAbilities_t::const_iterator find(const std::string& name) const;
				};
			}
		}
	}
}