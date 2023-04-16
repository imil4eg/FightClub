#pragma once

#include <unordered_set>
#include <unordered_map>

namespace FightClub::Server::Common
{
    class IConfigReader;
}

namespace FightClub::Server::Gateaway
{
    struct WebAddress 
    {
        std::string IP;
        std::string Port;
    };

    class ServicesContainer
    {
    private:
        using Services = std::unordered_map<std::string, WebAddress>;

    public:
        ServicesContainer(const Common::IConfigReader& configReader);

        bool isAuthRequired(const std::string& url) const
        {
            return m_authRequiredServices.find(url) != m_authRequiredServices.end();
        }

        bool isHttp(const std::string& url) const
        {
            return m_httpServices.find(url) != m_httpServices.end();
        }

        const WebAddress& get(const std::string& url) const
        {
            return ((isHttp(url)) ? m_httpServices.at(url) : m_websocketServices.at(url));
        }

        bool doesExist(const std::string& url) const
        {
            return isHttp(url) || m_websocketServices.find(url) != m_websocketServices.end();
        }

    private:
        void initializeServices(const Services& services, const std::string& sectionName);

    private:
        Services m_httpServices;
        Services m_websocketServices;
        std::unordered_set<std::string> m_authRequiredServices;
    };
}