#ifndef CHARACTER_FACTORY_H
#define CHARACTER_FACTORY_H

#include <memory>

#include "../CharacterStuff/IAttributesFactory.h"
#include "ICharacterFactory.h"

class CharacterFactory : public ICharacterFactory
{
private:
	IAttributesFactory* m_attributesFactory;

public:
	CharacterFactory(IAttributesFactory* attributesFactory) :
		m_attributesFactory{ attributesFactory }
	{
	}

public:
	std::unique_ptr<Player> createDefaultPlayer() override;

};

#endif // !CHARACTER_FACTORY_H

