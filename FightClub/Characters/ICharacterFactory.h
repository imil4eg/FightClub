#ifndef I_CHARACTER_FACTORY_H
#define I_CHARACTER_FACTORY_H

#include <string>

#include "Character.h"

class ICharacterFactory
{
public:
	virtual ~ICharacterFactory() noexcept = default;
	virtual std::unique_ptr<Character> createDefaultPlayer() = 0;
};

#endif // !I_CHARACTER_FACTORY_H

