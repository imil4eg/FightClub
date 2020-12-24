#pragma once

#include "IArmorStorage.h"
#include "Common/Configs/IConfig.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace armors
			{
				class ArmorStorage : public IArmorStorage
				{
				private:
					struct Impl;
					std::unique_ptr<Impl> pImpl;
					
				public:
					ArmorStorage(const common::configs::IConfig& config);
					~ArmorStorage();

					std::unique_ptr<Armor> getOrDefault(const boost::uuids::uuid& id) override;
					std::unique_ptr<Armor> getRandom(ArmorType armorType) override;
				};
			}
		}
	}
}