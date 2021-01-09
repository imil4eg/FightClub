#include <algorithm>
#include <set>

#include "CharacterStuff/Abilities/AbilitiesContainer.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace abilities
			{
				struct AbilitiesContainer::Impl
				{
					std::vector<std::unique_ptr<Ability>> m_abilities;
					std::vector<Ability*> m_abilitiesReferences;
					selectedAbilities_t m_selectedAbilities;
					int m_selectedAbilitiesCount;

					Impl(std::vector<std::unique_ptr<Ability>>&& abilities,
						selectedAbilityIds_t& selectedAbilityIds) :
						m_abilities{ std::move(abilities) },
						m_abilitiesReferences{},
						m_selectedAbilities{},
						m_selectedAbilitiesCount{}
					{
						std::set<boost::uuids::uuid> abilityIdsSet(std::begin(selectedAbilityIds), std::end(selectedAbilityIds));
						m_abilitiesReferences.reserve(abilities.size());
						for (auto it{ abilities.begin() }; it != abilities.end(); ++it)
						{
							m_abilitiesReferences.push_back(it->get());
						
							if (abilityIdsSet.find(it->get()->getId()) != abilityIdsSet.end())
							{
								m_selectedAbilities[m_selectedAbilitiesCount] = it->get();
								++m_selectedAbilitiesCount;
							}
						}
					}

					Impl() : 
						m_abilities{},
						m_abilitiesReferences{},
						m_selectedAbilities{},
						m_selectedAbilitiesCount{}
					{
					}

					~Impl() = default;
				};

				AbilitiesContainer::AbilitiesContainer(std::vector<std::unique_ptr<Ability>>&& abilities,
					selectedAbilityIds_t& selectedAbilityIds) :
					pImpl{ std::make_unique<Impl>(std::move(abilities), selectedAbilityIds) }
				{
				}

				AbilitiesContainer::AbilitiesContainer() :
					pImpl{ std::make_unique<Impl>() }
				{
				}

				AbilitiesContainer::~AbilitiesContainer() = default;

				const AbilitiesContainer::abilities_t& AbilitiesContainer::getAll() const
				{
					return pImpl->m_abilitiesReferences;
				}

				AbilitiesContainer::abilities_t::iterator AbilitiesContainer::get(const std::string& abilityName) const
				{
					// std::find does not work for some reason...
					for (auto it{ pImpl->m_abilitiesReferences.begin() }; it != pImpl->m_abilitiesReferences.end(); ++it)
					{
						if ((*it)->getName() == abilityName)
						{
							return it;
						}
					}

					return pImpl->m_abilitiesReferences.end();
				}

				const AbilitiesContainer::selectedAbilities_t& AbilitiesContainer::getSelected() const
				{
					return pImpl->m_selectedAbilities;
				}

				AbilitiesContainer::selectedAbilities_t& AbilitiesContainer::getSelected()
				{
					return pImpl->m_selectedAbilities;
				}
			}
		}
	}
}