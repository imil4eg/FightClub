#pragma once

#include "Fighter.hpp"

#include "JsonDefinitions.hpp"

namespace FightClub::Server::Fight {

            class Fighting : public std::enable_shared_from_this<Fighting>
            {
            public:
                enum class GameState
                {
                    prepration,
                    fighting,
                    end,
                    max_game_state
                };

                enum class MoveType
                {
                    attack,
                    spell,
                    max_move_type
                };

                enum class RequestType
                {
                    update,
                    request,
                    max_request_type
                };

            public:
                Fighting(FighterPtr firstPlayer, FighterPtr secondPlayer) :
                    m_firstPlayer(firstPlayer),
                    m_secondPlayer(secondPlayer),
                    m_isFirstPlayerMove(true)
                {
                }

                void start() const;

            private:
                void onPlayerResponseReceived(const std::string& response);

            private:
                FighterPtr m_firstPlayer;
                FighterPtr m_secondPlayer;

                bool m_isFirstPlayerMove;
            };

    void sendPreparationMessage(const json& playerCharacterJson, const json& enemyCharacterJson, Fighter& player);
    void processUserMove(FighterPtr player, FighterPtr opponent, const json& userMove);
    

}