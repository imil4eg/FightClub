#include "Network/AutoDiscoveryClient.hpp"

#include <fstream>

#include "Config/IConfigReader.hpp"
#include "Network/JsonAttributes.hpp"
#include "JsonDefinitions.hpp"
#include "WebsocketClient.hpp"

namespace FightClub::Server::Common
{
    void AutoDiscoveryClient::RegisterService()
    {
        ConfigDataPtr ip = m_configReader->get("AutoDiscoveryServiceIP");
        ConfigDataPtr port = m_configReader->get("AutoDiscoverySericePort");
        
        Network::WebsocketClient client(m_ios, ip->value, port->value);
        const auto error_code = co_await client.ConnectAsync();
        if (error_code) {
            throw std::runtime_error("could not connect to " + ip + " with port " + port + " error: " + error_code.message());
        }

        std::ifstream file(m_methodsConfigName);
        json file_json;
        file >> file_json;

        const std::string token = m_tokensFileReader->get("ServiceToken")->value;

        Network::RequestData request_data{"autodiscovery", token, http::verb::post, std::move(file_json), m_ip, m_port};
        const auto write_error_code = client.WriteAsync(std::move(request_data));
        if (write_error_code) {
            throw std::runtime_error("could not write auto discovery service. " + write_error_code.message());
        }
    }
}