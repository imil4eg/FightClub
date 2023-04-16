#pragma once

#include <boost/core/noncopyable.hpp>
#include <boost/beast/http/parser.hpp>

#include "BoostCommon.hpp"
#include "RequestProcesserContainer.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            class HttpConnection : public std::enable_shared_from_this<HttpConnection>, private boost::noncopyable
            {
                using stringBodyRequest_t = http::request<http::string_body>; 

            public:
                HttpConnection(tcp::socket&& socket, const RequestProcesserContainer& requestProcessers);
                ~HttpConnection();

                void start();

            private:
                void onRead(beast::error_code ec, std::size_t bytesTransfered);
                void close();
                void readData();
                void sendResponse(const std::string& body, http::status status);
                void onWriteFinished(beast::error_code ec, std::size_t bytesTransfered);
                void processRequest(const stringBodyRequest_t& request, RequestProcesser_t processer);

            private:
                beast::tcp_stream m_stream;
                const RequestProcesserContainer* m_requestProcessers;

                beast::flat_buffer m_buffer;

                std::unique_ptr<http::request_parser<http::string_body>> m_parser;

                std::unique_ptr<http::response<http::string_body>> m_sentResponse;
            };

        }
    }
}