#include "Characters/CharacterFactory.h"
#include "CharacterStuff/AttributeConsts.h"

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

				return std::make_unique<Player>(std::move(attributes), std::move(equipment), CharacterType::strong, std::move(nullptr));
			}
		}
	}
}