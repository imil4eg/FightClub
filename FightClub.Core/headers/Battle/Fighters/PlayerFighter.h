#pragma once

#include "Fighter.h"
#include "IO/IInputProcesser.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			namespace fighters
			{
				class PlayerFighter : public Fighter
				{
				private:
					io::IInputProcesser* m_inputProcesser;

				public:
					PlayerFighter(io::IMessageDisplayer& messageDisplayer, io::IInputProcesser& inputProcesser,
						characters::Character& player) :
						Fighter(messageDisplayer, player, "Player"),
						m_inputProcesser{ &inputProcesser }
					{
					}

					void playTurn(Fighter& target) override;

				private:
					battle::HitDirection askHitDirection();
				};
			}
		}
	}
}