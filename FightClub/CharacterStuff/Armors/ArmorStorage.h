#ifndef ARMOR_STORAGE_H
#define ARMOR_STORAGE_H

#include <map>
#include <vector>

#include "IArmorStorage.h"
#include "Armors.h"

class ArmorStorage : public IArmorStorage
{
private:
	std::map<boost::uuids::uuid, Armor*> m_armors{};
	std::vector<boost::uuids::uuid> m_armorIds{};

public:
	ArmorStorage()
	{
		initializeArmors();
	}

	const Armor* getOrDefault(const boost::uuids::uuid& id) override;
	const Armor* getRandom() override;

private:
	void initializeArmors();
};

#endif // !ARMOR_STORAGE_H

