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
				typedef nlohmann::detail::iteration_proxy_value<nlohmann::detail::iter_impl<nlohmann::json>> iter_json;

				struct AbilitiesStorage::Impl
				{
					common::configs::IConfig* m_config;

					Impl(common::configs::IConfig& config) :
						m_config{ &config }
					{
					}

					~Impl() = default;

					std::unique_ptr<Ability> createAbility(iter_json& abilityIt)
					{
						auto id{ boost::lexical_cast<boost::uuids::uuid>(abilityIt.value()[io::JsonAttributes::Id].get<std::string>()) };
						auto name{ abilityIt.value()[io::JsonAttributes::Name].get<std::string>() };
						auto type{ static_cast<AbilityType>(abilityIt.value()[io::JsonAttributes::Type].get<int>()) };
						auto cost{ abilityIt.value()[io::JsonAttributes::Cost].get<int>() };
						auto value{ abilityIt.value()[io::JsonAttributes::Value].get<int>() };
						auto duration{ abilityIt.value()[io::JsonAttributes::Duration].get<int>() };
					
						return std::make_unique<Ability>(std::move(id), std::move(name), type, cost, value, duration);
					}
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

						return pImpl->createAbility(ability);
					}

					return nullptr;
				}

				std::vector<std::unique_ptr<Ability>> AbilitiesStorage::get(AbilityType searchType) const
				{
					std::ifstream abilitiesFile{ pImpl->m_config->get(common::configs::ConfigKeys::abilitiesFile) };

					std::vector<std::unique_ptr<Ability>> abilities;

					if (!abilitiesFile.good())
						return abilities;

					json abilitiesJson;
					abilitiesFile >> abilitiesJson;

					int searchTypeInt{ static_cast<int>(searchType) };
					for (auto& ability : abilitiesJson[io::JsonAttributes::Abilities].items())
					{
						auto typeInt{ ability.value()[io::JsonAttributes::Type].get<int>() };

						if (typeInt != searchTypeInt)
							continue;

						abilities.push_back(pImpl->createAbility(ability));
					}

					return std::move(abilities);
				}
			}
		}
	}
}