#include "Connection.hpp"

#include <iostream>

#include <jwt-cpp/jwt.h>

#include "JsonAttributes.hpp"
#include "JsonDefinitions.hpp"
#include "IConfigReader.hpp"
#include "ConfigParams.hpp"
#include "HttpClient.hpp"
#include "WebsocketClient.hpp"

namespace FightClub::Server::Gateaway
{
    void Connection::start()
    {
        try
        {
            m_clientSocket.set_option(websocket::stream_base::decorator(
                [](websocket::response_type& res)
                {
                    res.set(http::field::server, std::string(BOOST_BEAST_VERSION_STRING) + " websocket-server-sync");
                }
            ));
                    
            m_clientSocket.async_accept(
                beast::bind_front_handler(
                    &Connection::acceptAsync,
                    shared_from_this()
                )
            );
        }
        catch (const beast::system_error& e)
        {
            if (e.code() != websocket::error::closed)
                std::cerr << "Error: " << e.code().message() << '\n';
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    void Connection::acceptAsync(const beast::error_code& ec)
    {
        if (ec)
        {
            std::cerr << "Error accept: " << ec.message() << '\n';
            return;
        }

        m_clientSocket.async_read(m_clientBuffer, beast::bind_front_handler(&Connection::onReadyAsync, shared_from_this()));
    }

    void Connection::onReadyAsync(const beast::error_code& ec, std::size_t bytesTransfered)
    {
        boost::ignore_unused(bytesTransfered);

        if (ec == http::error::end_of_stream || 
                    ec == net::error::eof)
        {
            std::cout << "User disconnected.\n";
            close();
            return;
        }

        if (ec)
        {
            std::cout << "read error: " << ec.message() << '\n';
            return;
        }

        json message{json::parse(beast::buffers_to_string(m_clientBuffer.data()))};
        if (!message.contains(JsonAttributes::Target))
        {
            sendErrorToClientAsync("No target specified.", http::status::bad_request);
            return;
        }

        std::string target{message[JsonAttributes::Target].get<std::string>()};
        if (!m_servicesContainer->doesExist(target))
        {
            sendErrorToClientAsync("Specified url doesn't exist.", http::status::not_found);
            return;
        }
        
        if (!m_servicesContainer->isAuthRequired(target) && !isValidToken(message))
        {
            sendErrorToClientAsync("Invalid token.", http::status::network_authentication_required);
            return;
        }

        m_userRequestBody = message[JsonAttributes::Body];
        processRequest(target, m_servicesContainer->isHttp(target));
    }

    void Connection::sendErrorToClientAsync(const std::string& message, http::status status)
    {
        json response;
        response[JsonAttributes::Error] = message;
        response[JsonAttributes::Status] = status;
        sendMessageToClientAsync(response);
    }

    void Connection::sendMessageToClientAsync(const json& message)
    {

        m_clientSocket.async_write(net::buffer(message.dump()),
                                beast::bind_front_handler(
                                    &Connection::onWriteToClientAsync,
                                    shared_from_this()
                                ));
    }

    void Connection::onWriteToClientAsync(const beast::error_code& err, std::size_t bytesTransferred)
    {
        boost::ignore_unused(bytesTransferred);

        if (err)
        {
            std::cerr << "write error: " << err.message() << '\n';
            return;
        }

        m_clientSocket.async_read(m_clientBuffer, beast::bind_front_handler(&Connection::onReadyAsync, shared_from_this()));
    }

    void Connection::close()
    {
        m_clientSocket.close(tcp::socket::shutdown_send);
    }

    bool Connection::isValidToken(const json& message)
    {
        if (!message.contains(JsonAttributes::Token))
        {
            return false;
        }

        using JWT = Common::ConfigParams::JWT;

        auto verifier = jwt::verify()
                                .allow_algorithm(jwt::algorithm::hs256{m_configReader->get(JWT::Key)->value})
                                .with_issuer(m_configReader->get(JWT::Issuer)->value)
                                .with_type(m_configReader->get(JWT::Type)->value)
                                .with_claim(m_configReader->get(JWT::PayloadClaimID)->value, 
                                            jwt::claim(m_configReader->get(JWT::Claim)->value));

        try
        {
            verifier.verify(jwt::decode(message[JsonAttributes::Token].get<std::string>()));
        }
        catch (const std::exception& ex)
        {
            return false;
        }

        return true;
    }

    void Connection::processRequest(const std::string& target, bool isHttp)
    {
        if (isHttp)
        {
            m_serviceConnection = std::make_unique<Common::HttpClient>(m_ios, hostAndPort.IP, hostAndPort.Port);
        }
        else
        {
            m_serviceConnection = std::make_unique<Common::HttpClient>(m_ios, hostAndPort.IP, hostAndPort.Port);
        }

        const WebAddress& hostAndPort = m_servicesContainer->get(target);
        m_serviceConnection->connectAsync(std::bind(&Connection::onServiceConnected, shared_from_this(), std::placeholders::_1));
    }

    void Connection::onServiceConnected(bool isSuccessfull)
    {
        if (!isSuccessfull)
        {
            std::cerr << "Couldn't connect to service.\n";
            return;
        }

        json body{json::parse(m_userRequestBody)};
        m_serviceConnection->writeAsync(body, std::bind(&Connection::onServiceResponseReceived, shared_from_this(), std::placeholders::_1, 
                                                                                                                    std::placeholders::_2));
    }

    void Connection::onServiceResponseReceived(const std::string& body, http::status status)
    {
        json response;
        response[JsonAttributes::Status] = status;
        response[JsonAttributes::Body] = body;

        m_clientSocket.async_write(net::buffer(response.dump()), beast::bind_front_handler(&Connection::onWebsocketWriteAsync, shared_from_this()));
    }

    void Connection::onWebsocketWriteAsync(const beast::error_code& ec, std::size_t bytesWritten)
    {
        boost::ignore_unused(bytesWritten);
        
        if (ec)
        {
            std::cerr << "Error on write to client: " << ec.message() << '\n';
            return;
        }

        m_serviceConnection.release();
        m_clientSocket.async_read(m_clientBuffer, beast::bind_front_handler(&Connection::onReadyAsync, shared_from_this())); 
    }
}