#pragma once

#include "Common/Configs/IConfig.h"
#include "IAbilitiesStorage.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace abilities
			{
				class AbilitiesStorage : public IAbilitiesStorage
				{
				private:
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				public:
					AbilitiesStorage(common::configs::IConfig& config);
					~AbilitiesStorage();

					std::unique_ptr<Ability> getOrDefault(const boost::uuids::uuid& id) const override;
					std::vector<std::unique_ptr<Ability>> get(AbilityType type) const override;
				};
			}
		}
	}
}