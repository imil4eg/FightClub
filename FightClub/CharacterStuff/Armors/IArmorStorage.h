#ifndef I_ARMOR_STORAGE_H
#define I_ARMOR_STORAGE_H

#include <boost/uuid/uuid.hpp>
#include <memory>

#include "Armor.h"

class IArmorStorage
{
public:
	virtual ~IArmorStorage() = default;

	virtual std::unique_ptr<Armor> getOrDefault(const boost::uuids::uuid& id) = 0;
	virtual std::unique_ptr<Armor> getRandom(Armor::Type armorType) = 0;
};

#endif // !I_ARMOR_STORAGE_H

