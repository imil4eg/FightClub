#include "Bot.h"
#include "BotFactory.h"
#include "../Character.h"


Bot BotFactory::create(const Character& player) const
{
	//TODO: Generate bot depend on character attributes

	auto* const attribute = new Attributes{ 100, 1, 1, 1 };
	auto* const equipment = new Equipment{};
	auto* const weapon = new Weapon{ 10 };
	return Bot{ attribute, equipment, weapon };
}
