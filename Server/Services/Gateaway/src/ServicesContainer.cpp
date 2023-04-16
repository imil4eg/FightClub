#include "ServicesContainer.hpp"

#include "IConfigReader.hpp"

namespace FightClub::Server::Gateaway
{
    ServicesContainer::ServicesContainer(const Common::IConfigReader& configReader)
    {
        initializeServices(m_httpServices, "httpServices");
        initializeServices(m_websocketServices, "websocketServices");
    }

    void ServicesContainer::initializeServices(const Services& services, const std::string& sectionName) 
    {
        Common::ConfigDataPtr section = configReader.get(sectionName);
        for (auto it = section->values.begin(); it != section->values.end(); ++it)
        {
            WebAddress address{it->second->value["ip"]->value, it->second->value["port"]};
            services.insert({it->second->values["url"]->value, address});
            if (it->second->values["is_auth"]->value == "true")
            {
                m_authRequiredServices.insert(it->second->value["url"]);
            }
        }
    }
}