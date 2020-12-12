#ifndef MESSAGE_DISPLAYER_H
#define MESSAGE_DISPLAYER_H

#include <string>
#include <iostream>

#include "../Battle/HitDirection.h"

namespace fightclub
{
	namespace io
	{
		class MessageDisplayer
		{
		public:
			static void cmdLineBeggining()
			{
				std::cout << "FightClub>";
			}

			static void displayPlayerHit(int damage, battle::HitDirection hitDirection)
			{
				displayHit("Player", "Enemy", damage, hitDirection);
			}

			static void displayEnemyHit(int damage, battle::HitDirection hitDirection)
			{
				displayHit("Enemy", "Player", damage, hitDirection);
			}

			static void displayPlayerTurn()
			{
				std::cout << "Your turn!\n\n";
			}

			static void displayPlayerHP(int hp)
			{
				displayHP("Your", hp);
			}

			static void displayEnemyHP(int hp)
			{
				displayHP("Enemys", hp);
			}

			static void startFighting()
			{
				std::cout << "The fighting beggins!\n\n";
			}

			static void battleResult(bool playerWon)
			{
				if (playerWon)
					std::cout << "You win!\n";
				else
					std::cout << "You lost!\n";
			}

		private:
			static void displayHit(std::string name, std::string targetName, int damage, battle::HitDirection hitDirection)
			{
				std::cout << name << " hits " << targetName << " to " << hitDirection << " on " << damage << " damage.\n";
			}

			static void displayHP(std::string name, int hp)
			{
				std::cout << name << " HP: " << hp << '\n';
			}
		};

	}
}

#endif // !MESSAGE_DISPLAYER_H



