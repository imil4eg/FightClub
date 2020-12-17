#pragma once

#include "Common/Configs/IConfig.h"
#include "IWeaponStorage.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace weapons
			{
				class WeaponStorage : public IWeaponStorage
				{
				private:
					const common::configs::IConfig* m_config;

				public:
					WeaponStorage(const common::configs::IConfig& config) :
						m_config{ &config }
					{
					}

					std::unique_ptr<Weapon> getWeaponOrDefault(const boost::uuids::uuid& id) const override;
					std::unique_ptr<Weapon> getRandomWeapon() const override;
				};
			}
		}
	}
}