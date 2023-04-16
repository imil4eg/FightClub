#pragma once

#include "Fighter.hpp"

namespace FightClub::Server::Fight {

            class IOpponentSearcher 
            {
            public:
                virtual ~IOpponentSearcher() = default;

                inline void search(FighterPtr fighter)
                {
                    searchImpl(fighter);
                }

            private:
                virtual void searchImpl(FighterPtr fighter) = 0;
            };
}