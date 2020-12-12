#ifndef BOT_FACTORY_H
#define BOT_FACTORY_H

#include <memory>

#include "Bot.h"
#include "IBotFactory.h"
#include "../../CharacterStuff/IAttributesFactory.h"
#include "../../CharacterStuff/Armors/IArmorStorage.h"
#include "../../CharacterStuff/Weapons/IWeaponStorage.h"

namespace fightclub
{
	namespace characters
	{
		namespace bots
		{
			class BotFactory : public IBotFactory
			{
			private:
				const int m_attributeDependOnTypeExchangeValue = 20;
				const int m_minAttributeValue = 1;

				characterstuff::IAttributesFactory* m_attributeFactory;
				characterstuff::weapons::IWeaponStorage* m_weaponStorage;
				characterstuff::armors::IArmorStorage* m_armorStorage;

			public:
				BotFactory(characterstuff::IAttributesFactory* attributeFactory,
					characterstuff::weapons::IWeaponStorage* weaponStorage,
					characterstuff::armors::IArmorStorage* armorStorage) :
					m_attributeFactory{ attributeFactory },
					m_weaponStorage{ weaponStorage },
					m_armorStorage{ armorStorage }
				{
				}

				Bot create(const Character& player) override;

			private:
				void calculateAttributeValueToAdd(int& attributeValueToIncrease, int& attribueteValueToDecrease);
				void calculateAttributes(int& strength, int& agility, CharacterType characterType);
			};
		}
	}
}

#endif // !BOT_FACTORY_H

