#ifndef MENU_H
#define MENU_H

#include <memory>

#include "Battle/IBattle.h"
#include "Common/Configs/IPlayerConfig.h"
#include "IMenu.h"
#include "IO/Savers/GameDataProcesser.h"

class Menu : public IMenu
{
private:
	IBattle* m_battle;
	IPlayerConfig* m_playerConfig;
	GameDataProcesser* m_gameDataProcesser;

public:
	Menu(IBattle* battle,
	     IPlayerConfig* playerConfig,
		 GameDataProcesser* gameDataProcesser) :
		m_battle{ battle },
		m_playerConfig{ playerConfig },
		m_gameDataProcesser{gameDataProcesser}
	{
	}

	void show() const override;
};

#endif // !MENU_H

