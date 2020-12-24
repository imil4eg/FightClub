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
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				public:
					PlayerFighter(const io::IMessageDisplayer& messageDisplayer, const io::IInputProcesser& inputProcesser, 
								  characters::Character& player);
					~PlayerFighter();

					void playTurn(Fighter& target) override;
				};
			}
		}
	}
}