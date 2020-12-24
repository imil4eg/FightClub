#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <exception>
#include <string>
#include <fstream>

#include "Common/RandomGenerator.h"
#include "CharacterStuff/Weapons/WeaponStorage.h"
#include "IO/JsonAttributes.h";

#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace weapons
			{
				struct WeaponStorage::Impl
				{
					const common::configs::IConfig* m_config;

					Impl(const common::configs::IConfig& config) :
						m_config{ &config }
					{
					}
				};

				WeaponStorage::WeaponStorage(const common::configs::IConfig& config) :
					pImpl{ std::make_unique<Impl>(config) }
				{
				}

				WeaponStorage::~WeaponStorage() = default;

				std::unique_ptr<Weapon> WeaponStorage::getRandomWeapon() const
				{
					std::ifstream input{ pImpl->m_config->get(common::configs::ConfigKeys::weaponsFile) };

					if (!input.good())
						return nullptr;

					json weaponsJson;
					input >> weaponsJson;

					std::vector<Weapon> weapons{};
					for (auto& weapon : weaponsJson[io::JsonAttributes::Weapons].items())
					{
						auto id{ boost::lexical_cast<boost::uuids::uuid>(weapon.value()[io::JsonAttributes::Id].get<std::string>()) };
						auto name{ weapon.value()[io::JsonAttributes::Name].get<std::string>() };
						int damage{ weapon.value()[io::JsonAttributes::Damage].get<int>() };

						weapons.push_back(Weapon{ id, name, damage });
					}

					auto randomWeaponId{ common::RandomGenerator::getBetween(0, static_cast<int>(weapons.size()) - 1) };

					return std::make_unique<Weapon>(weapons[randomWeaponId]);
				}

				std::unique_ptr<Weapon> WeaponStorage::getWeaponOrDefault(const boost::uuids::uuid& id) const
				{
					std::ifstream input{ pImpl->m_config->get(common::configs::ConfigKeys::weaponsFile) };

					if (!input.good())
						return nullptr;

					json weaponsJson;
					input >> weaponsJson;

					auto idStr{ boost::lexical_cast<std::string>(id) };
					for (auto& weapon : weaponsJson[io::JsonAttributes::Weapons].items())
					{
						if (idStr != weapon.value()[io::JsonAttributes::Id].get<std::string>())
						{
							continue;
						}

						auto id{ boost::lexical_cast<boost::uuids::uuid>(weapon.value()[io::JsonAttributes::Id].get<std::string>()) };
						auto name{ weapon.value()[io::JsonAttributes::Name].get<std::string>() };
						int damage{ weapon.value()[io::JsonAttributes::Damage].get<int>() };

						return std::make_unique<Weapon>(id, name, damage);
					}

					return nullptr;
				}

			}
		}
	}
}