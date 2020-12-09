#ifndef WEAPON_STORAGE_H
#define WEAPON_STORAGE_H

#include <map>

#include "IWeaponStorage.h"
#include "../../Common/Configs/IConfig.h"

class WeaponStorage : public IWeaponStorage
{
private:
	const std::string m_weaponsKey{ "weapons" };
	const std::string m_idKey{ "id" };
	const std::string m_nameKey{ "name" };
	const std::string m_damageKey{ "damage" };

	const IConfig* m_config;

public:
	WeaponStorage(const IConfig& config) : 
		m_config{&config}
	{
	}

	std::unique_ptr<Weapon> getWeaponOrDefault(const boost::uuids::uuid& id) const override;
	std::unique_ptr<Weapon> getRandomWeapon() const override;
};

#endif // !WEAPON_STORAGE_H

