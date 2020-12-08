#ifndef BOT_FACTORY_H
#define BOT_FACTORY_H

#include <memory>

#include "Bot.h"
#include "IBotFactory.h"
#include "../../CharacterStuff/IAttributesFactory.h"
#include "../../CharacterStuff/Armors/IArmorStorage.h"
#include "../../CharacterStuff/IWeaponStorage.h"

class BotFactory : public IBotFactory
{
private:
	const int m_attributeDependOnTypeExchangeValue = 20;
	const int m_minAttributeValue = 1;

	IAttributesFactory* m_attributeFactory;
	IWeaponStorage* m_weaponStorage;
	IArmorStorage* m_armorStorage;

public:
	BotFactory(IAttributesFactory* attributeFactory, 
			   IWeaponStorage* weaponStorage,
			   IArmorStorage* armorStorage) :
		m_attributeFactory{ attributeFactory },
		m_weaponStorage{weaponStorage},
		m_armorStorage{armorStorage}
	{
	}

	Bot create(const Character& player) override;

private:
	void calculateAttributeValueToAdd(int& attributeValueToIncrease, int& attribueteValueToDecrease);
	void calculateAttributes(int& strength, int& agility, CharacterType characterType);
};


#endif // !BOT_FACTORY_H

