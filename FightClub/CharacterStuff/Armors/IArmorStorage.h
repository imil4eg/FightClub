#ifndef I_ARMOR_STORAGE_H
#define I_ARMOR_STORAGE_H

#include "Armor.h"

class IArmorStorage
{
public:
	virtual ~IArmorStorage() = default;

	virtual const Armor* getOrDefault(const boost::uuids::uuid& id) = 0;
	virtual const Armor* getRandom() = 0;
};

#endif // !I_ARMOR_STORAGE_H

