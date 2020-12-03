#ifndef WEAPON_STORAGE_H
#define WEAPON_STORAGE_H

#include <map>

#include "IWeaponStorage.h"
#include "Weapons/BrassKnucklesWithKnife.h"
#include "Weapons/Claymore.h"
#include "Weapons/Knife.h"
#include "Weapons/PoorBrassKnuckles.h"
#include "Weapons/Rapier.h"

class WeaponStorage : public IWeaponStorage
{
private:
	std::map<boost::uuids::uuid, Weapon> m_weapons{};
	std::vector<boost::uuids::uuid> m_weaponIds{};

public:
	WeaponStorage()
	{
		auto knucles{ BrassKnucklesWithKnife{} };
		m_weapons.insert(std::make_pair(knucles.getId(), knucles));
		m_weaponIds.push_back(knucles.getId());
		auto claymor{ Claymore{} };
		m_weapons.insert(std::make_pair(claymor.getId(), claymor));
		m_weaponIds.push_back(claymor.getId());
		auto knife{ Knife{} };
		m_weapons.insert(std::make_pair(knife.getId(), knife));
		m_weaponIds.push_back(knife.getId());
		auto poorKnucles{ PoorBrassKnuckles{} };
		m_weapons.insert(std::make_pair(poorKnucles.getId(), poorKnucles));
		m_weaponIds.push_back(poorKnucles.getId());
		auto rapier{ Rapier{} };
		m_weapons.insert(std::make_pair(rapier.getId(), rapier));
		m_weaponIds.push_back(rapier.getId());
	}

	const Weapon* getWeapon(const boost::uuids::uuid& id) const override;
	const Weapon* getRandomWeapon() const override;
};

#endif // !WEAPON_STORAGE_H

