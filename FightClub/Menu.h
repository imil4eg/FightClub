#ifndef MENU_H
#define MENU_H

#include "IMenu.h"

class Menu : public IMenu
{
public:
	void show() const override;
};

#endif // !MENU_H

