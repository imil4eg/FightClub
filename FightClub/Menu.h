#ifndef MENU_H
#define MENU_H

#include <memory>

#include "Battle/IBattle.h"
#include "IMenu.h"

class Menu : public IMenu
{
private:
	const std::shared_ptr<IBattle> m_battle;

public:
	Menu(const std::shared_ptr<IBattle>& battle) : m_battle{ battle }
	{
	}

	void show() const override;
};

#endif // !MENU_H

