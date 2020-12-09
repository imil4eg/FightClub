#ifndef ARMOR_STORAGE_H
#define ARMOR_STORAGE_H

#include <map>
#include <vector>

#include "IArmorStorage.h"
#include "../../Common/Configs/IConfig.h"

class ArmorStorage : public IArmorStorage
{
private:
	const std::string m_armorsKey{ "armors" };
	const std::string m_idKey{ "id" };
	const std::string m_nameKey{ "name" };
	const std::string m_typeKey{ "type" };
	const std::string m_valueKey{ "value" };

	const IConfig* m_confilg;

public:
	ArmorStorage(const IConfig& config) :
		m_confilg{ &config }
	{
	}

	std::unique_ptr<Armor> getOrDefault(const boost::uuids::uuid& id) override;
	std::unique_ptr<Armor> getRandom(Armor::Type armorType) override;
};

#endif // !ARMOR_STORAGE_H

