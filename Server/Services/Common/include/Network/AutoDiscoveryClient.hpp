#pragma once

#include "BoostCommon.hpp"

namespace FightClub::Server::Common 
{
    class IConfigReader;

    class AutoDiscoveryClient
    {
    public:
        AutoDiscoveryClient(net::io_service& ios, const IConfigReader& configReader, std::string methodsConfigName,
                            std::string ip, std::string port, const IConfigReader& tokensFileReader) :
            m_ios{ios},
            m_configReader(&configReader),
            m_methodsConfigName(std::move(methodsConfigName)),
            m_ip(std::move(ip)),
            m_port(std::move(port)),
            m_tokensFileReader(&tokensFileReader)
        {
        }

        void RegisterService();

    private:
        net::io_service& m_ios;
        const IConfigReader* m_configReader;
        const std::string m_methodsConfigName;
        std::string m_ip;
        std::string m_port;
        const IConfigReader* m_tokensFileReader;
    };
}