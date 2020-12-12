#ifndef MENU_H
#define MENU_H

#include <memory>

#include "Battle/IBattle.h"
#include "Common/Configs/IPlayerConfig.h"
#include "IMenu.h"
#include "IO/Savers/GameDataProcesser.h"

namespace fightclub
{
	class Menu : public IMenu
	{
	private:
		battle::IBattle* m_battle;
		common::configs::IPlayerConfig* m_playerConfig;
		io::savers::GameDataProcesser* m_gameDataProcesser;

	public:
		Menu(battle::IBattle* battle,
			common::configs::IPlayerConfig* playerConfig,
			io::savers::GameDataProcesser* gameDataProcesser) :
			m_battle{ battle },
			m_playerConfig{ playerConfig },
			m_gameDataProcesser{ gameDataProcesser }
		{
		}

		void show() const override;
	};
}

#endif // !MENU_H

