#pragma once

#include <mutex>
#include <unordered_map>

#include "FighterConnection.hpp"
#include "IOpponentSearcher.hpp"

namespace FightClub::Server::Fight {

            class OpponentSearcher : public IOpponentSearcher
            {
            private:
                void searchImpl(FighterPtr fighter) override;

                void onUserDisconnected(int userId);

            private:
                std::unordered_map<int, FighterPtr> m_fighters;
                std::mutex m_mutex;
            };
}