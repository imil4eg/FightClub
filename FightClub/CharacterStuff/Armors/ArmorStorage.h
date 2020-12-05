#ifndef ARMOR_STORAGE_H
#define ARMOR_STORAGE_H

#include <map>
#include <vector>

#include "IArmorStorage.h"
#include "Armors.h"

class ArmorStorage : public IArmorStorage
{
private:
	const int m_headStartIndex = 0;
	const int m_headEndIndex = 2;
	const int m_cuirasseStartIndex = 3;
	const int m_cuirasseEndIndex = 5;
	const int m_legsStartIndex = 6;
	const int m_legsEndIndex = 8;
	
	std::map<boost::uuids::uuid, Armor*> m_armors{};
	std::vector<boost::uuids::uuid> m_armorIds{};

public:
	ArmorStorage()
	{
		initializeArmors();
	}

	const Armor* getOrDefault(const boost::uuids::uuid& id) override;
	const Armor* getRandom(Armor::Type armorType) override;

private:
	void initializeArmors();
};

#endif // !ARMOR_STORAGE_H

