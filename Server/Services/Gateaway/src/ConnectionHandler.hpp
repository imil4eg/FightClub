#pragma once

#include "BaseConnectionHandler.hpp"

#include "Connection.hpp"

namespace FightClub::Server::Common
{
    class IConfigReader;
}

namespace FightClub::Server::Gateaway
{
    class ConnectionHandler : public Common::BaseConnectionHandler
    {
    public:
        ConnectionHandler(net::io_service& ios, const std::string& host, const std::string& port, 
                            const ServicesContainer& servicesContainer,
                            const Common::IConfigReader& configReader) :
            BaseConnectionHandler(ios, host, port),
            m_ios{ios},
            m_servicesContainer(&servicesContainer),
            m_configReader(&configReader)
        {
        }

    private:
        void startConnection(tcp::socket&& socket) override
        {
            std::make_shared<Connection>(std::move(socket), m_ios, *m_servicesContainer, *m_configReader)->start();
        }

    private:
        net::io_service& m_ios;
        const ServicesContainer* m_servicesContainer;
        const Common::IConfigReader* m_configReader;
    };
}