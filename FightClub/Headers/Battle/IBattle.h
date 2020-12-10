#ifndef IBATTLE_H
#define IBATTLE_H

#include "../Characters/Character.h"

class IBattle
{
public:
	virtual ~IBattle() noexcept = default;
	virtual void fightWithBot(Character& player) = 0;
};

#endif // !IBATTLE_H


