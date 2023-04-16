#pragma once

#include <unordered_map>

#include "BoostCommon.hpp"
#include "ConnectionClient.hpp"
#include "ServicesContainer.hpp"

namespace FightClub::Server::Common 
{
    class IConfigReader;
}

namespace FightClub::Server::Gateaway
{
    class Connection : public std::enable_shared_from_this<Connection>
    {
    public:
        explicit Connection(tcp::socket&& socket, net::io_service& ios,
                            const ServicesContainer& servicesContainer,
                            const Common::IConfigReader& configReader) :
            m_clientSocket(std::move(socket)),
            m_ios{ios},
            m_servicesContainer(&servicesContainer),
            m_configReader(&configReader)
        {
        }

        void start();

    private:
        void acceptAsync(const beast::error_code& ec);
        void onReadyAsync(const beast::error_code& ec, std::size_t bytesTransfered);
        void close();
        void sendMessageToClientAsync(const json& message);
        void onWriteToClientAsync(const beast::error_code& err, std::size_t bytesTransferred);
        void sendErrorToClientAsync(const std::string& message, http::status status);
        void sendRequestToServiceAsync();
        
        void processRequest(const std::string& target, bool isHttp);
        void onServiceConnected(bool isSuccessfull);
        void onServiceResponseReceived(const std::string& body, http::status);

        void onWebsocketWriteAsync(const beast::error_code& ec, std::size_t bytesWritten);
        
        bool isValidToken(const json& message);

    private:
        websocket::stream<tcp::socket> m_clientSocket;
        net::io_service& m_ios;
        const ServicesContainer* m_servicesContainer;
        const Common::IConfigReader* m_configReader;

        std::string m_userRequestBody;
        beast::flat_buffer m_clientBuffer;
        std::unique_ptr<Common::ConnectionClient> m_serviceConnection;
    };
}