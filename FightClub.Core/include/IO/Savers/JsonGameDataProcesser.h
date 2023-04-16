#pragma once

#include "GameDataProcesser.h"
#include "CharacterStuff/IAttributesFactory.h"
#include "CharacterStuff/Armors/IArmorStorage.h"
#include "CharacterStuff/Weapons/IWeaponStorage.h"
#include "CharacterStuff/Abilities/IAbilitiesStorage.h"
#include "Common/Configs/IConfig.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace fightclub
{
	namespace core
	{
		namespace io
		{
			namespace savers
			{
				class JsonGameDataProcesser : public GameDataProcesser
				{
				private:
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				public:
					JsonGameDataProcesser(characterstuff::IAttributesFactory& attributeFactory,
						characterstuff::weapons::IWeaponStorage& weaponStorage,
						characterstuff::armors::IArmorStorage& armorStorage,
						characterstuff::abilities::IAbilitiesStorage& abilitiesStorage,
						common::configs::IConfig& config);
					~JsonGameDataProcesser();

					std::unique_ptr<characters::Player> load() override;
					void save(characters::Player& player) const override;
				};
			}
		}
	}
}