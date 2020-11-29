#ifndef BOT_FACTORY_H
#define BOT_FACTORY_H

#include "Bot.h"
#include "IBotFactory.h"

class BotFactory : public IBotFactory
{
public:
	BotFactory() = default;

	Bot create(const Character& player) const override;
};


#endif // !BOT_FACTORY_H

