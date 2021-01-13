#ifndef MENU_H
#define MENU_H

#include <memory>

#include "Battle/IBattle.h"
#include "Common/Configs/IPlayerConfig.h"
#include "CharacterStuff/IInventoryManager.h"
#include "CharacterStuff/IAttributesManager.h"
#include "CharacterStuff/Abilities/IAbilitiesManager.h"
#include "IMenu.h"
#include "IO/Savers/GameDataProcesser.h"
#include "IO/IInputProcesser.h"

namespace fightclub
{
	class Menu : public IMenu
	{
	private:
		core::battle::IBattle* m_battle;
		core::common::configs::IPlayerConfig* m_playerConfig;
		core::io::savers::GameDataProcesser* m_gameDataProcesser;
		core::io::IInputProcesser* m_inputProcesser;
		core::characterstuff::IInventoryManager* m_inventoryManager;
		core::characterstuff::IAttributesManager* m_attributesManger;
		core::characterstuff::abilities::IAbilitiesManager* m_abilitiesManager;

	public:
		Menu(core::battle::IBattle& battle,
			core::common::configs::IPlayerConfig& playerConfig,
			core::io::savers::GameDataProcesser& gameDataProcesser,
			core::io::IInputProcesser& inputProcesser,
			core::characterstuff::IInventoryManager& inventoryManager,
			core::characterstuff::IAttributesManager& attributesManager,
			core::characterstuff::abilities::IAbilitiesManager& abilitiesManager):
			m_battle{ &battle },
			m_playerConfig{ &playerConfig },
			m_gameDataProcesser{ &gameDataProcesser },
			m_inputProcesser{ &inputProcesser },
			m_inventoryManager{&inventoryManager},
			m_attributesManger{&attributesManager},
			m_abilitiesManager{&abilitiesManager}
		{
		}

		void show() const override;
	};
}

#endif // !MENU_H

