#ifndef I_CHARACTER_FACTORY_H
#define ICHARACTER_FACTORY_H

#include <string>

#include "Character.h"

class ICharacterFactory
{
public:
	virtual ~ICharacterFactory() noexcept = default;
	virtual Character* createDefaultPlayer() = 0;
};

#endif // !I_CHARACTER_FACTORY_H

