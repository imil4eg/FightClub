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
				struct Impl;
				std::unique_ptr<Impl> pImpl;

			public:
				Battle(characters::bots::IBotFactory& botFactory, fighters::IFighterFactory& fighterFactory,
					io::IMessageDisplayer& messageDisplayer);

				~Battle();

				void fightWithBot(characters::Character& player) override;
			};
		}
	}
}