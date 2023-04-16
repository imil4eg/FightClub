#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <fstream>
#include <exception>

#include "CharacterStuff/Armors/ArmorStorage.h"
#include "Common/RandomGenerator.h"
#include "IO/JsonAttributes.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace armors
			{
				struct ArmorStorage::Impl
				{
					const common::configs::IConfig* m_confilg;

					Impl(const common::configs::IConfig& config) :
						m_confilg{ &config }
					{
					}

					~Impl() = default;
				};

				ArmorStorage::ArmorStorage(const common::configs::IConfig& config) :
					pImpl{ std::make_unique<Impl>(config) }
				{
				}

				ArmorStorage::~ArmorStorage() = default;

				std::unique_ptr<Armor> ArmorStorage::getOrDefault(const boost::uuids::uuid& id)
				{
					std::ifstream armorsFile{ pImpl->m_confilg->get(common::configs::ConfigKeys::armorsFile) };

					if (!armorsFile.good())
						return nullptr;

					json armorsJson;
					armorsFile >> armorsJson;

					auto idStr{ boost::lexical_cast<std::string>(id) };
					for (auto& armor : armorsJson[io::JsonAttributes::Armors].items())
					{
						if (idStr != armor.value()[io::JsonAttributes::Id].get<std::string>())
						{
							continue;
						}

						auto id{ boost::lexical_cast<boost::uuids::uuid>(armor.value()[io::JsonAttributes::Id].get<std::string>()) };
						auto name{ armor.value()[io::JsonAttributes::Name].get<std::string>() };
						auto type{ static_cast<characterstuff::armors::ArmorType>(armor.value()[io::JsonAttributes::Type].get<int>()) };
						auto armorValue{ armor.value()[io::JsonAttributes::Value].get<int>() };

						return std::make_unique<Armor>(id, name, type, armorValue);
					}

					return nullptr;
				}

				std::unique_ptr<Armor> ArmorStorage::getRandom(characterstuff::armors::ArmorType armorType)
				{
					std::ifstream armorsFile{ pImpl->m_confilg->get(common::configs::ConfigKeys::armorsFile) };

					if (!armorsFile.good())
						return nullptr;

					json armorsJson;

					auto armorTypeInt{ static_cast<int>(armorType) };
					std::vector<Armor> armors{};
					for (auto& armorJson : armorsJson[io::JsonAttributes::Armors].items())
					{
						if (armorTypeInt != armorJson.value()[io::JsonAttributes::Type].get<int>())
						{
							continue;
						}

						auto id{ boost::lexical_cast<boost::uuids::uuid>(armorJson.value()[io::JsonAttributes::Id].get<std::string>()) };
						auto name{ armorJson.value()[io::JsonAttributes::Name].get<std::string>() };
						auto type{ static_cast<characterstuff::armors::ArmorType>(armorJson.value()[io::JsonAttributes::Type].get<int>()) };
						auto armorValue{ armorJson.value()[io::JsonAttributes::Value].get<int>() };

						Armor armor{ id, name, type, armorValue };
						armors.push_back(armor);
					}

					auto randomArmorId{ common::RandomGenerator::getBetween(0, armors.size()) };

					if (randomArmorId == armors.size())
					{
						return nullptr;
					}

					return std::make_unique<Armor>(std::move(armors[randomArmorId]));

					return nullptr;
				}
			}
		}
	}
}