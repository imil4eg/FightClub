#pragma once

#include <memory>

#include "BoostCommon.hpp"
#include "JsonDefinitions.hpp"

namespace FightClub::Server::Common
{
    template<typename TClientType>
    class ConnectionClient : public std::enable_shared_from_this<TClientType>
    {
    public:
        using ConnectionReadyHandler = std::function<void(bool)>;
        using ResponseHandler = std::function<void(const std::string&, http::status)>;

    public:
        ConnectionClient(net::io_service& ios, std::string host, std::string port) :
            m_ios{ios},
            m_host(std::move(host)),
            m_port(std::move(port))
        {
        }

        virtual ~ConnectionClient()
        {
            close();
        }

        void connectAsync(ConnectionReadyHandler connectedHandler) 
        {
            m_connectionReadyHandler = connectedHandler;
            tcp::resolver resolver{m_ios};
            resolver.async_resolve(m_host, m_port, beast::bind_front_handler(&ConnectionClient::handleResolve, std::enable_shared_from_this<TClientType>::shared_from_this()));
        }

        void writeAsync(const json& body, ResponseHandler responseHandler)
        {
            m_responseHandler = responseHandler;
            writeAsyncImpl(body);
        }

        void close()
        {
            closeImpl();
        }

    protected:
        void clearConnectionReadyHandler()
        {
            m_connectionReadyHandler = nullptr;
        }

        void executeConnectionReadyHandler(bool success)
        {
            m_connectionReadyHandler(success);
        }

        void clearResponseHandler() 
        {
            m_responseHandler = nullptr;
        }

        void executeResponseHandler(const std::string& message, http::status status)
        {
            m_responseHandler(message, status);
        }

    private:
        virtual void writeAsyncImpl(const json& body) = 0;
        virtual void handleResolve(const beast::error_code& ec, tcp::resolver::results_type results) = 0;
        virtual void closeImpl() = 0;

    private:
        net::io_service& m_ios;
        std::string m_host;
        std::string m_port;

        ConnectionReadyHandler m_connectionReadyHandler;
        ResponseHandler m_responseHandler;
    };
}