#include "HttpClient.hpp"

#include <iostream>

namespace FightClub::Server::Common 
{
    void HttpClient::handleResolve(const beast::error_code& ec, tcp::resolver::results_type results)
    {
        if (ec)
        {
            std::cerr << "Resolve failed. " << ec.message() << '\n';
            executeConnectionReadyHandler(false);
            clearConnectionReadyHandler();
            return;
        }

        m_stream.async_connect(results, beast::bind_front_handler(&HttpClient::handleConnect, shared_from_this()));
    }

    void HttpClient::handleConnect(const beast::error_code& ec, tcp::resolver::results_type::endpoint_type)
    {
        if (ec)
        {
            std::cerr << "Connection failed. " << ec.message() << '\n';
            executeConnectionReadyHandler(false);
            return; 
        }

        executeConnectionReadyHandler(true);
        clearConnectionReadyHandler();
    }

    void HttpClient::writeAsyncImpl(const json& body)
    {
        m_sentRequest = std::make_unique<http::request<http::string_body>>();
        m_sentRequest->body() = body.dump();
        m_sentRequest->prepare_payload();
        
        http::async_write(m_stream, *m_sentRequest.get(), beast::bind_front_handler(&HttpClient::onWriteFinisihed, shared_from_this()));
    }

    void HttpClient::onWriteFinisihed(const beast::error_code& ec, std::size_t bytesTransfered)
    {
        boost::ignore_unused(bytesTransfered);

        if (ec)
        {
            std::cerr << "Write error. " << ec.message() << '\n';
            executeResponseHandler(ec.message(), http::status::internal_server_error);
            clearResponseHandler();
            return;
        }

        http::async_read(m_stream, m_buffer, *m_responseParser.get(), 
                        beast::bind_front_handler(&HttpClient::onReadAsync, shared_from_this()));
    }

    void HttpClient::onReadAsync(const beast::error_code& ec, std::size_t bytesTransfered)
    {
        boost::ignore_unused(bytesTransfered);

        if (ec == http::error::end_of_stream)
        {
            close();
            executeResponseHandler("Connection closed.", http::status::connection_closed_without_response);
            clearResponseHandler();
            return;
        }

        if (ec)
        {
            std::cerr << "Read error. " << ec.message() << '\n';
            executeResponseHandler(ec.message(), http::status::internal_server_error);
            clearResponseHandler();
            return; 
        }

        auto response = m_responseParser->release();
        
        executeResponseHandler(response.body(), response.result());
        clearResponseHandler();
    }

    void HttpClient::closeImpl()
    {
        m_stream.socket().shutdown(tcp::socket::shutdown_send);
    }
}