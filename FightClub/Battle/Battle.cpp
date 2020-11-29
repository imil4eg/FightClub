#include <exception>
#include <iostream>

#include "Battle.h"
#include "../Characters/Bots/Bot.h"
#include "../IO/MessageDisplayer.h"
#include "HitDirection.h"

void FightPreparation(Character& player, Character& enemy)
{
	player.restoreHp();
	enemy.restoreHp();
}

void Battle::fightWithBot(Character& player)
{
	auto bot{ m_botFactory->create(player) };
	
	MessageDisplayer::startFighting();
	
	FightPreparation(player, bot);

	bool playerWon{};
	while (true)
	{
		player.playTurn(bot);

		if (bot.getAttributes()->getHp() <= 0)
		{
			playerWon = true;
			break;
		}

		bot.playTurn(player);

		if (player.getAttributes()->getHp() <= 0)
		{
			break;
		}
	}

	MessageDisplayer::battleResult(playerWon);
}