#pragma once

#include <functional>

#include "Common/Configs/IPlayerConfig.h"
#include "IInventoryManager.h"

namespace fightclub
{
	namespace characterstuff
	{
		class InventoryManager : public IInventoryManager
		{
		private:
			IPlayerConfig* m_playerConfig;

		public:
			InventoryManager(IPlayerConfig& playerConfig) :
				m_playerConfig{ &playerConfig }
			{
			}

			void enterMenu() override;
			void displayCurrentEquipment() override;
			void displayWeapons() override;
			void displayArmors() override;

		private:
			template<typename T>
			void display(std::vector<T>& elements, std::string itemName, std::function<void(T&)> displayFunc);
		};
	}
}
