#ifndef I_WEAPON_STORAGE_H
#define I_WEAPON_STORAGE_H

#include <memory>
#include <boost/uuid/uuid.hpp>

#include "Weapon.h"

class IWeaponStorage
{
public:
	virtual ~IWeaponStorage() noexcept = default;
	virtual std::unique_ptr<Weapon> getWeaponOrDefault(const boost::uuids::uuid& id) const = 0;
	virtual std::unique_ptr<Weapon> getRandomWeapon() const = 0;
};

#endif // !I_WEAPON_STORAGE_H

