#include "FighterConnectionHandler.hpp"

#include <iostream>

#include "IFighterBuilderFactory.hpp"
#include "IOpponentSearcher.hpp"

namespace FightClub::Server::Fight {

    void FighterConnectionHandler::startConnection(tcp::socket&& socket)
    {
        std::cout << "Connection received\n";
                    
        auto connection = std::make_shared<FighterConnection>(std::move(socket));
        connection->start([this](std::shared_ptr<FighterConnection> fighter)
        {
           m_fighterBuilderFactory->create(fighter, 
                    std::bind(&IOpponentSearcher::search, m_opponentSearcher, std::placeholders::_1))->startAsync();
        });
    }    

}