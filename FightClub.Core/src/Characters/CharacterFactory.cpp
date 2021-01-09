#include "Characters/CharacterFactory.h"
#include "CharacterStuff/AttributeConsts.h"
#include "CharacterStuff/Abilities/DynamicAbilitiesContainer.h"

namespace fightclub
{
	namespace core
	{
		namespace characters
		{
			std::unique_ptr<Player> CharacterFactory::createDefaultPlayer()
			{
				int initialAttributeValue{ 1 * characterstuff::AttributeConsts::AttributesPerLevelMultiplier };
				auto attributes{ m_attributesFactory->create(nullptr, 1, initialAttributeValue, initialAttributeValue, CharacterType::strong) };
				auto equipment{ std::make_unique<characterstuff::DynamicEquipment>() };
				auto abilitiesContainer{ std::make_unique<characterstuff::abilities::DynamicAbilitiesContainer>() };

				return std::make_unique<Player>(std::move(attributes), std::move(equipment), CharacterType::strong, 
											    std::make_unique<characterstuff::Inventory>(), std::move(abilitiesContainer));
			}
		}
	}
}