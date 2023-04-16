#pragma once

#include "CharacterStuff/IAttributesFactory.h"
#include "CharacterStuff/Weapons/IWeaponStorage.h"
#include "CharacterStuff/Armors/IArmorStorage.h"
#include "CharacterStuff/Abilities/IAbilitiesStorage.h"
#include "IBotFactory.h"

namespace fightclub
{
	namespace core
	{
		namespace characters
		{
			namespace bots
			{
				class BotFactory : public IBotFactory
				{
				private:
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				public:
					BotFactory(characterstuff::IAttributesFactory& attributeFactory,
						characterstuff::weapons::IWeaponStorage& weaponStorage,
						characterstuff::armors::IArmorStorage& armorStorage,
						characterstuff::abilities::IAbilitiesStorage& abilityStorage);

					~BotFactory();

					Bot create(const Character& player) override;
				};
			}
		}
	}
}