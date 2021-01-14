#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <fstream>

#include "CharacterStuff/Abilities/AbilitiesStorage.h"
#include "Common/Configs/ConfigKeys.h"
#include "IO/JsonAttributes.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace abilities
			{
				struct AbilitiesStorage::Impl
				{
					common::configs::IConfig* m_config;

					Impl(common::configs::IConfig& config) :
						m_config{ &config }
					{
					}

					~Impl() = default;
				};

				AbilitiesStorage::AbilitiesStorage(common::configs::IConfig& config) :
					pImpl(std::make_unique<Impl>(config))
				{
				}

				AbilitiesStorage::~AbilitiesStorage() = default;

				std::unique_ptr<Ability> AbilitiesStorage::getOrDefault(const boost::uuids::uuid& id) const
				{
					std::ifstream abilitiesFile{ pImpl->m_config->get(common::configs::ConfigKeys::abilitiesFile) };

					if (!abilitiesFile.good())
						return nullptr;

					json abilitiesJson;
					abilitiesFile >> abilitiesJson;

					auto idStr{ boost::lexical_cast<std::string>(id) };
					for (auto& ability : abilitiesJson[io::JsonAttributes::Abilities].items())
					{
						if (idStr != ability.value()[io::JsonAttributes::Id].get<std::string>())
						{
							continue;
						}

						auto id{ boost::lexical_cast<boost::uuids::uuid>(ability.value()[io::JsonAttributes::Id].get<std::string>()) };
						auto name{ ability.value()[io::JsonAttributes::Name].get<std::string>() };
						auto type{ static_cast<AbilityType>(ability.value()[io::JsonAttributes::Type].get<int>()) };
						auto cost{ ability.value()[io::JsonAttributes::Cost].get<int>() };
						auto damage{ ability.value()[io::JsonAttributes::Damage].get<int>() };
						auto duration{ ability.value()[io::JsonAttributes::Duration].get<int>() };

						return std::make_unique<Ability>(std::move(id), std::move(name), type, cost, damage, duration);
					}

					return nullptr;
				}
			}
		}
	}
}