#pragma once

#include "IO/IMessageDisplayer.h"
#include "Characters/Bots/IBotFactory.h"
#include "IBattle.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			class Battle : public IBattle
			{
			private:
				characters::bots::IBotFactory* m_botFactory;
				io::IMessageDisplayer* m_messageDisplayer;

			public:
				Battle(characters::bots::IBotFactory& botFactory, io::IMessageDisplayer& messageDisplayer) :
					m_botFactory{ &botFactory },
					m_messageDisplayer{ &messageDisplayer }
				{
				}

				void fightWithBot(characters::Character& player) override;
			};
		}
	}
}