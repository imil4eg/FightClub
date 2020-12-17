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
					const common::configs::IConfig* m_confilg;

				public:
					ArmorStorage(const common::configs::IConfig& config) :
						m_confilg{ &config }
					{
					}

					std::unique_ptr<Armor> getOrDefault(const boost::uuids::uuid& id) override;
					std::unique_ptr<Armor> getRandom(ArmorType armorType) override;
				};
			}
		}
	}
}