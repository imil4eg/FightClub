#pragma once

namespace fightclub 
{
	namespace characterstuff 
	{
		class IInventoryManager
		{
		public:
			virtual ~IInventoryManager() = default;
			virtual void enterMenu() = 0;
			virtual void displayCurrentEquipment() = 0;
			virtual void displayWeapons() = 0;
			virtual void displayArmors() = 0;
		};
	}
}
