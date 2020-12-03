#ifndef BOT_FACTORY_H
#define BOT_FACTORY_H

#include <memory>

#include "Bot.h"
#include "IBotFactory.h"
#include "../../CharacterStuff/IAttributesFactory.h"
#include "../../CharacterStuff/IWeaponStorage.h"

class BotFactory : public IBotFactory
{
private:
	const int m_attributeDependOnTypeExchangeValue = 20;
	const int m_minAttributeValue = 1;

	const std::shared_ptr<IAttributesFactory> m_attributeFactory;
	const std::shared_ptr<IWeaponStorage> m_weaponStorage;

public:
	BotFactory(const std::shared_ptr<IAttributesFactory>& attributeFactory, const std::shared_ptr<IWeaponStorage>& weaponStorage) :
		m_attributeFactory{ attributeFactory },
		m_weaponStorage{weaponStorage}
	{
	}

	Bot create(const Character& player) override;

private:
	void calculateAttributeValueToAdd(int& attributeValueToIncrease, int& attribueteValueToDecrease);
	void calculateAttributes(int& strength, int& agility, CharacterType characterType);
};


#endif // !BOT_FACTORY_H

