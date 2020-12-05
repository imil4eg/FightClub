#ifndef JSON_GAME_SAVER_H
#define JSON_GAME_SAVER_H

#include <memory>

#include "GameDataProcesser.h"
#include "../../CharacterStuff/IAttributesFactory.h"
#include "../../CharacterStuff/IWeaponStorage.h"
#include "../../CharacterStuff/Armors/IArmorStorage.h"

#include "../../libs/nlohmann/json.hpp"

using json = nlohmann::json;


class JsonGameDataProcesser : public GameDataProcesser
{
private:
	const std::string m_headAttribute{ "head" };
	const std::string m_cuirasseAttribute{ "cuirasse" };
	const std::string m_legsAttribute{ "legs" };

	std::shared_ptr<IAttributesFactory> m_attributesFactory;
	std::shared_ptr<IWeaponStorage> m_weaponStorage;
	std::shared_ptr<IArmorStorage> m_armorStorage;

public:
	JsonGameDataProcesser(const std::shared_ptr<IAttributesFactory>& attributeFactory, 
		const std::shared_ptr<IWeaponStorage>& weaponStorage,
		const std::shared_ptr<IArmorStorage>& armorStorage) :
		m_attributesFactory{ attributeFactory },
		m_weaponStorage{weaponStorage},
		m_armorStorage{armorStorage}
	{
	}

	Character* load() override;
	void save(Character& character) const override;

private:
	const Armor* getArmor(json& j, const std::string& attributeName);
};


#endif // !JSON_GAME_SAVER_H

