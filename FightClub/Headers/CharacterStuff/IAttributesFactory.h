#ifndef I_ATTRIBUTES_FACTORY_H
#define I_ATTRIBUTES_FACTORY_H

#include <memory>

#include "Attributes.h"
#include "../Characters/CharacterType.h"
#include "Weapons/Weapon.h"

namespace fightclub
{
	namespace characterstuff
	{
		class IAttributesFactory
		{
		public:
			virtual ~IAttributesFactory() noexcept = default;
			virtual std::unique_ptr<Attributes> create(const weapons::Weapon* const weapon, int level, int stength, int agility, characters::CharacterType characterType) = 0;
		};
	}
}


#endif // !IATTRIBUTES_FACTORY_H

