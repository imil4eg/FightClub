#include "HttpConnection.hpp"

#include <iostream>

#include <boost/uuid/uuid_generators.hpp>

#include "NetworkExceptions.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            HttpConnection::HttpConnection(tcp::socket&& socket, const RequestProcesserContainer& requestProcessers) : 
                m_stream(std::move(socket)),
                m_requestProcessers(&requestProcessers),
                m_parser(std::make_unique<http::request_parser<http::string_body>>())
            {
            }

            HttpConnection::~HttpConnection() = default;

            void HttpConnection::start()
            {
                net::dispatch(m_stream.get_executor(), 
                                beast::bind_front_handler(&HttpConnection::readData, shared_from_this()));
            }

            void HttpConnection::readData()
            {
                http::async_read(m_stream, m_buffer, *m_parser.get(), beast::bind_front_handler(&HttpConnection::onRead, shared_from_this()));
            }

            void HttpConnection::onRead(beast::error_code ec, std::size_t bytesTransfered)
            {
                boost::ignore_unused(bytesTransfered);

                if (ec == http::error::end_of_stream)
                {
                    close();
                    return;
                }

                if (ec)
                {
                    std::cerr << "read: " << ec.message() << '\n';
                    return;
                }

                auto request = m_parser->release();

                try
                {
                    RequestProcesser_t processer = m_requestProcessers->get(request.target().to_string(), request.method());
                    processRequest(request, processer);
                }
                catch (const UriNotFoundException& e)
                {
                    sendResponse(e.what(), http::status::not_found);
                }
                catch (const MethodNotAllowedException& e)
                {
                    sendResponse(e.what(), http::status::method_not_allowed);
                }
                catch (const InvalidParameterException& e)
                {
                    sendResponse(e.what(), http::status::bad_request);
                }
                catch (const DataError& e)
                {
                    sendResponse(e.what(), http::status::ok);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    sendResponse(e.what(), http::status::internal_server_error);
                }
            }

            void HttpConnection::close()
            {
                beast::error_code ec;
                m_stream.socket().shutdown(tcp::socket::shutdown_send, ec);
            }

            void HttpConnection::sendResponse(const std::string& body, http::status status)
            {
                m_sentResponse = std::make_unique<http::response<http::string_body>>(status, 11);
                m_sentResponse->body() = body;
                m_sentResponse->prepare_payload();
                http::async_write(m_stream, *m_sentResponse.get(), beast::bind_front_handler(&HttpConnection::onWriteFinished, shared_from_this()));
            }

            void HttpConnection::onWriteFinished(beast::error_code ec, std::size_t bytesTransfered)
            {
                boost::ignore_unused(bytesTransfered);

                m_sentResponse = nullptr;

                if (ec)
                {
                    std::cout << "write failed. Message: " << ec.message() << '\n';
                    return;
                }
            }

            void HttpConnection::processRequest(const stringBodyRequest_t& request, RequestProcesser_t processer)
            {
                json bodyJson = json::parse(request.body());
                json responseBody = processer(bodyJson);

                sendResponse(responseBody.dump(), http::status::ok);
            }
        }
    }
}