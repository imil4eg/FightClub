#pragma once

#include "CharacterModel.hpp"
#include "ConnectionDefinitions.hpp"

namespace FightClub::Server::Fight {

            class Fighter
            {
            public:
                Fighter(Common::CharacterModelPtr character, FighterConnectionPtr connection) :
                    m_character(std::move(character)),
                    m_connection(connection),
                    m_leftHP{m_character->getAttribute().getHealth()},
                    m_leftStamina{m_character->getAttribute().getStamina()}
                {
                }

                const Common::CharacterModel* getCharacter() const
                {
                    return m_character.get();
                }

                inline void sendMessage(const std::string& message)
                {
                    m_connection->requestAsync(message, nullptr);
                }

                inline void requestMove(const std::string& message, FighterConnection::ReadHandler readHandler)
                {
                    m_connection->requestAsync(message, readHandler);
                }
                

            private:
                Common::CharacterModelPtr m_character;
                FighterConnectionPtr m_connection;

                int m_leftHP;
                int m_leftStamina;
            };

            using FighterPtr = std::shared_ptr<Fighter>;
}