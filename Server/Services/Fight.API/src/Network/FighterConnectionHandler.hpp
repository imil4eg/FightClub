#pragma once

#include "BaseConnectionHandler.hpp"
#include "FighterBuilder.hpp"

namespace FightClub::Server::Fight {

            class IFighterBuilderFactory;
            class IOpponentSearcher;

            class FighterConnectionHandler : public Common::BaseConnectionHandler
            {
            public:
                FighterConnectionHandler(net::io_service& ios, const std::string& address, const std::string& port,
                                         IFighterBuilderFactory& fighterBuilderFactory,
                                         IOpponentSearcher& opponentSearcher) :
                                        Common::BaseConnectionHandler(ios, address, port),
                                        m_fighterBuilderFactory(&fighterBuilderFactory),
                                        m_opponentSearcher(&opponentSearcher)
                {
                }
                
            private:
                void startConnection(tcp::socket&& socket) override;

            private:
                IFighterBuilderFactory* m_fighterBuilderFactory;
                IOpponentSearcher* m_opponentSearcher;
            };

}