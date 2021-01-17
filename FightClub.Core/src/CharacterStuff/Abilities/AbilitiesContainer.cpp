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
					
					Impl(std::vector<std::unique_ptr<Ability>>&& abilities,
						selectedAbilityIds_t& selectedAbilityIds) :
						m_abilities{ std::move(abilities) },
						m_abilitiesReferences{},
						m_selectedAbilities{}
					{
						std::set<boost::uuids::uuid> abilityIdsSet(std::begin(selectedAbilityIds), std::end(selectedAbilityIds));
						m_abilitiesReferences.reserve(m_abilities.size());
						
						int selectedAbilitiesCounter{};
						for (auto it{ m_abilities.begin() }; it != m_abilities.end(); ++it)
						{							
							if (abilityIdsSet.find(it->get()->getId()) != abilityIdsSet.end())
							{
								m_selectedAbilities[selectedAbilitiesCounter] = it->get();
								++selectedAbilitiesCounter;
							}
							else
							{
								m_abilitiesReferences.push_back(it->get());
							}
						}
					}

					Impl() : 
						m_abilities{},
						m_abilitiesReferences{},
						m_selectedAbilities{}
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

				AbilitiesContainer::selectedAbilities_t& AbilitiesContainer::getSelectedForEditing()
				{
					return pImpl->m_selectedAbilities;
				}

				AbilitiesContainer::abilities_t& AbilitiesContainer::getAllAbilitiesForEditing()
				{
					return pImpl->m_abilitiesReferences;
				}

				AbilitiesContainer::selectedAbilities_t::const_iterator AbilitiesContainer::find(const std::string& name) const
				{
					return std::find_if(pImpl->m_selectedAbilities.begin(), pImpl->m_selectedAbilities.end(),
						[&](const Ability* ability)
						{
							return ability != nullptr && ability->getName() == name;
						});
				}
			}
		}
	}
}