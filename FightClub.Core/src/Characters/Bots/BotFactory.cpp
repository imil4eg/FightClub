#include "Characters/Bots/BotFactory.h"
#include "Common/RandomGenerator.h"
#include "CharacterStuff/Abilities/AbilitiesContainer.h"

namespace fightclub
{
	namespace core
	{
		namespace characters
		{
			namespace bots
			{
				struct BotFactory::Impl
				{
					const int m_attributeDependOnTypeExchangeValue = 20;
					const int m_minAttributeValue = 1;

					characterstuff::IAttributesFactory* m_attributeFactory;
					characterstuff::weapons::IWeaponStorage* m_weaponStorage;
					characterstuff::armors::IArmorStorage* m_armorStorage;
					characterstuff::abilities::IAbilitiesStorage* m_abilityStorage;

					Impl(characterstuff::IAttributesFactory& attributeFactory,
						characterstuff::weapons::IWeaponStorage& weaponStorage,
						characterstuff::armors::IArmorStorage& armorStorage,
						characterstuff::abilities::IAbilitiesStorage& abilityStorage) : 
						m_attributeFactory{ &attributeFactory },
						m_weaponStorage{ &weaponStorage },
						m_armorStorage{ &armorStorage },
						m_abilityStorage{&abilityStorage}
					{
					}

					~Impl() = default;

					void calculateAttributeValueToAdd(int& attributeValueToIncrease, int& attribueteValueToDecrease)
					{
						int possibleValueToExchange{ attribueteValueToDecrease - ((attribueteValueToDecrease < m_attributeDependOnTypeExchangeValue) ? m_minAttributeValue : m_attributeDependOnTypeExchangeValue) };

						attributeValueToIncrease += possibleValueToExchange;
						attribueteValueToDecrease -= possibleValueToExchange;
					}

					void calculateAttributes(int& strength, int& agility, CharacterType botCharacterType)
					{
						switch (botCharacterType)
						{
						case CharacterType::strong:
						{
							calculateAttributeValueToAdd(strength, agility);
							break;
						}
						case CharacterType::smooth:
							calculateAttributeValueToAdd(agility, strength);
							break;
						default:
							throw std::out_of_range("Not implemented CharacterType.");
						}
					}
					
					std::unique_ptr<characterstuff::abilities::AbilitiesContainer> getAbilities()
					{
						// TODO: Add and other abilities for bot instead of only traps.

						auto traps{ m_abilityStorage->get(characterstuff::abilities::AbilityType::trap) };

						characterstuff::abilities::AbilitiesContainer::selectedAbilityIds_t selectedAbilitiesIds;

						for (int i{ 0 }; i < selectedAbilitiesIds.size() && i < traps.size(); ++i)
						{
							selectedAbilitiesIds[i] = traps[i]->getId();
						}

						return std::make_unique<characterstuff::abilities::AbilitiesContainer>(std::move(traps), selectedAbilitiesIds);
					}
				};

				BotFactory::BotFactory(characterstuff::IAttributesFactory& attributeFactory,
					characterstuff::weapons::IWeaponStorage& weaponStorage,
					characterstuff::armors::IArmorStorage& armorStorage,
					characterstuff::abilities::IAbilitiesStorage& abilityStorage) :
					pImpl(std::make_unique<Impl>(attributeFactory, weaponStorage, armorStorage, abilityStorage))
				{
				}

				BotFactory::~BotFactory() = default;

				Bot BotFactory::create(const Character& player)
				{
					auto botCharacterType{ static_cast<CharacterType>(common::RandomGenerator::getBetween(0, static_cast<int>(CharacterType::max_character_type) - 1)) };

					int strength = player.getAttributes()->getStrength();
					int agility = player.getAttributes()->getAgility();

					pImpl->calculateAttributes(strength, agility, botCharacterType);

					auto weapon{ pImpl->m_weaponStorage->getRandomWeapon() };

					auto botAttributes{ pImpl->m_attributeFactory->create(weapon.get(), player.getAttributes()->getLevel(), strength, agility, botCharacterType) };

					auto head{	   pImpl->m_armorStorage->getRandom(characterstuff::armors::ArmorType::head) };
					auto cuirasse{ pImpl->m_armorStorage->getRandom(characterstuff::armors::ArmorType::body) };
					auto boots{	   pImpl->m_armorStorage->getRandom(characterstuff::armors::ArmorType::legs) };
					auto equipment{ std::make_unique<characterstuff::StaticEquipment>(std::move(head), std::move(cuirasse), std::move(boots)) };
					auto abilitiesContainer{ pImpl->getAbilities() };

					return Bot{ std::move(botAttributes), std::move(equipment), std::move(abilitiesContainer), botCharacterType, std::move(weapon) };
				}
			}
		}
	}
}