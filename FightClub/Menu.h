#ifndef MENU_H
#define MENU_H

#include <memory>

#include "Battle/IBattle.h"
#include "Common/Configs/IPlayerConfig.h"
#include "IMenu.h"

class Menu : public IMenu
{
private:
	const std::shared_ptr<IBattle> m_battle;
	const std::shared_ptr<IPlayerConfig> m_playerConfig;

public:
	Menu(const std::shared_ptr<IBattle>& battle, 
		 const std::shared_ptr<IPlayerConfig>& playerConfig) :
		m_battle{ battle },
		m_playerConfig{ playerConfig }
	{
	}

	void show() const override;
};

#endif // !MENU_H

