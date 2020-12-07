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
	const std::shared_ptr<IBattle> m_battle;
	const std::shared_ptr<IPlayerConfig> m_playerConfig;
	const std::shared_ptr<GameDataProcesser> m_gameDataProcesser;

public:
	Menu(const std::shared_ptr<IBattle>& battle,
	     const std::shared_ptr<IPlayerConfig>& playerConfig,
		 const std::shared_ptr<GameDataProcesser>& gameDataProcesser) :
		m_battle{ battle },
		m_playerConfig{ playerConfig },
		m_gameDataProcesser{gameDataProcesser}
	{
	}

	void show() const override;
};

#endif // !MENU_H

