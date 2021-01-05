#include "CharacterStuff/AttributeConsts.h"
#include "CharacterStuff/BaseAttributesManager.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			struct BaseAttributesManager::Impl
			{
				IAttributesFactory* m_attributesFactory;
				
				int m_tempIncreasedStrength{};
				int m_tempIncreasedAgility{};

				Impl(IAttributesFactory& attributesFactory) :
					m_attributesFactory{ &attributesFactory }
				{
				}

				int& getAttributeValueAddress(AttributeType attributeType)
				{
					return (attributeType == AttributeType::strong) ? m_tempIncreasedStrength : m_tempIncreasedAgility;
				}
			};

			BaseAttributesManager::BaseAttributesManager(IAttributesFactory& attributesFactory) :
				pImpl{ std::make_unique<Impl>(attributesFactory) }
			{
			}

			BaseAttributesManager::~BaseAttributesManager() = default;

			void BaseAttributesManager::increaseAttribute(characters::Character& character, AttributeType attributeType, int value)
			{
				int leftAttributesPoints{ BaseAttributesManager::calculateLeftAttributePoints(character) };

				if (value > leftAttributesPoints)
					throw std::out_of_range("Enterd value to increase " + std::to_string(value) +
						" higher than left attributes points " + std::to_string(leftAttributesPoints));

				pImpl->getAttributeValueAddress(attributeType) += value;
			}

			void BaseAttributesManager::decreaseAttribute(characters::Character& character, AttributeType attributeType, int value)
			{
				int specifiedAttributeValue = (attributeType == AttributeType::strong ?
					character.getAttributes()->getStrength() + pImpl->m_tempIncreasedStrength :
					character.getAttributes()->getAgility() + pImpl->m_tempIncreasedAgility) - value;

				if (specifiedAttributeValue < 1)
				{
					throw std::out_of_range("The " + core::characterstuff::to_string(attributeType) + 
						" can't be decreased on " + std::to_string(value) + " due to would be lower than 1.");
				}

				pImpl->getAttributeValueAddress(attributeType) -= value;
			}

			void BaseAttributesManager::saveChanges(characters::Character& character)
			{
				if (pImpl->m_tempIncreasedStrength == 0 &&
					pImpl->m_tempIncreasedAgility == 0)
				{
					return;
				}

				auto& characterAttributes{ *character.getAttributes() };

				int totalStrength{ characterAttributes.getStrength() + pImpl->m_tempIncreasedStrength };
				int totalAgility{ characterAttributes.getAgility() + pImpl->m_tempIncreasedAgility };

				character.updateAttributes(std::move(pImpl->m_attributesFactory->create(character, totalStrength, totalAgility)));
				
				pImpl->m_tempIncreasedStrength = 0;
				pImpl->m_tempIncreasedAgility = 0;
			}

			int BaseAttributesManager::calculateLeftAttributePoints(characters::Character& character) const
			{
				auto attributes{ character.getAttributes() };
				int characterUserAttributePoints{ attributes->getStrength() + attributes->getAgility()};
				
				int attributesByLevelUpgradePoints{ attributes->getLevel() * AttributeConsts::AttributesPerLevelMultiplier };
				int levelUpgradeStrength{ attributesByLevelUpgradePoints };
				int levelUpgradeAgility{ attributesByLevelUpgradePoints };

				int characterUserUpgradeAttributePerLevelMaxPoints{ (attributes->getLevel() * AttributeConsts::UserCharacterUpgradeAttributePerLevel) 
					- pImpl->m_tempIncreasedStrength - pImpl->m_tempIncreasedAgility };

				int maxCharacterAttributes{ levelUpgradeAgility + levelUpgradeStrength + characterUserUpgradeAttributePerLevelMaxPoints };

				return maxCharacterAttributes - characterUserAttributePoints;
			}
		}
	}
}