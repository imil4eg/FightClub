#ifndef WEAPON_STORAGE_H
#define WEAPON_STORAGE_H

#include <map>

#include "IWeaponStorage.h"
#include "../../Common/Configs/IConfig.h"

namespace fightclub
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

#endif // !WEAPON_STORAGE_H

