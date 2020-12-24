#ifndef MENU_H
#define MENU_H

#include <memory>

#include "Battle/IBattle.h"
#include "Common/Configs/IPlayerConfig.h"
#include "CharacterStuff/IInventoryManager.h"
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
		//fightclub::characterstuff::IInventoryManager* m_inventoryManager;

	public:
		Menu(core::battle::IBattle& battle,
			core::common::configs::IPlayerConfig& playerConfig,
			core::io::savers::GameDataProcesser& gameDataProcesser,
			core::io::IInputProcesser& inputProcesser):
			m_battle{ &battle },
			m_playerConfig{ &playerConfig },
			m_gameDataProcesser{ &gameDataProcesser },
			m_inputProcesser{ &inputProcesser }
		{
		}

		void show() const override;
	};
}

#endif // !MENU_H

