#pragma once

#include "Characters/Bots/IBotFactory.h"
#include "Fighters/IFighterFactory.h"
#include "IBattle.h"
#include "IO/IMessageDisplayer.h"

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
				fighters::IFighterFactory* m_fighterFactory;
				io::IMessageDisplayer* m_messageDisplayer;

			public:
				Battle(characters::bots::IBotFactory& botFactory, fighters::IFighterFactory& fighterFactory,
					   io::IMessageDisplayer& messageDisplayer) :
					m_botFactory{ &botFactory },
					m_fighterFactory{&fighterFactory},
					m_messageDisplayer{&messageDisplayer}
				{
				}

				void fightWithBot(characters::Character& player) override;
			};
		}
	}
}