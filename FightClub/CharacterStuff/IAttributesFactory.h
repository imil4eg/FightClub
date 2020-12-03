#ifndef I_ATTRIBUTES_FACTORY_H
#define I_ATTRIBUTES_FACTORY_H

#include "Attributes.h"
#include "../Characters/CharacterType.h"
#include "Weapon.h"

class IAttributesFactory
{
public:
	virtual ~IAttributesFactory() noexcept = default;
	virtual Attributes create(const Weapon* const weapon, int level, int stength, int agility, CharacterType characterType) = 0;
};


#endif // !IATTRIBUTES_FACTORY_H

