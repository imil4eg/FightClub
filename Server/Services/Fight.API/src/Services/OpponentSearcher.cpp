#include "OpponentSearcher.hpp"

#include "Fighting.hpp"

namespace FightClub::Server::Fight {

            void OpponentSearcher::searchImpl(FighterPtr fighter)
            {
                std::lock_guard lock(m_mutex);

                if (m_fighters.empty()) 
                {
                    m_fighters.insert({fighter->getCharacter()->getId(), fighter});
                    return;
                }  

                auto opponent = m_fighters.begin()->second;
                m_fighters.erase(opponent->getCharacter()->getId());

                std::make_shared<Fighting>(fighter, opponent);
            }
            
}