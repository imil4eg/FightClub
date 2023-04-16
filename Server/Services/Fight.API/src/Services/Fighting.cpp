#include "Fighting.hpp"

#include <functional>

#include "FightMessages.hpp"
#include "JsonDefinitions.hpp"
#include "FightJsonAttributes.hpp"
#include "ModelToJsonMapper.hpp"

namespace FightClub::Server::Fight {

    void Fighting::start() const
    {
        json firstPlayerJson = Common::CharacterToJson(*m_firstPlayer->getCharacter());
        json secondPlayerJson = Common::CharacterToJson(*m_secondPlayer->getCharacter());

        sendPreparationMessage(firstPlayerJson, secondPlayerJson, *m_firstPlayer.get());
        sendPreparationMessage(secondPlayerJson, firstPlayerJson, *m_secondPlayer.get());

        json moveRequest;
        moveRequest[FightJsonAttributes::gameState] = GameState::fighting;
        moveRequest[FightJsonAttributes::requestType] = RequestType::request;
        m_firstPlayer->requestMove(moveRequest.dump(), std::bind(&Fighting::onPlayerResponseReceived, shared_from_this(), std::placeholders::_1));
    }

    void Fighting::onPlayerResponseReceived(const std::string& response)
    {
        json responseJson{json::parse(response)};
        if (m_isFirstPlayerMove)
        {
        }
        else
        {
        }
    }

    void sendPreparationMessage(const json& playerCharacterJson, const json& enemyCharacterJson, Fighter& player)
    {
        json message;
        message[FightJsonAttributes::gameState] = Fighting::GameState::prepration;
        message[FightJsonAttributes::character] = playerCharacterJson;
        message[FightJsonAttributes::enemy] = enemyCharacterJson;

        player.sendMessage(message.dump());
    }

    void processUserMove(FighterPtr player, FighterPtr opponent, const json& userMove)
    {
        auto moveType = userMove[FightJsonAttributes::moveType].get<Fighting::MoveType>();

        switch (moveType)
        {
            case Fighting::MoveType::attack:
            {
                break;
            }
            case Fighting::MoveType::spell:
            {
                break;
            }
            default:
                throw std::runtime_error("Unsupported move type.");
        }
    }
}