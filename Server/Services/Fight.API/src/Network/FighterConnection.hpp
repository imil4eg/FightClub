#pragma once

#include <memory>
#include <functional>

#include <boost/beast/websocket.hpp>

#include "BoostCommon.hpp"

class Fighting;

namespace FightClub {
    namespace Server {
        namespace Fight {

            class FighterConnection : public std::enable_shared_from_this<FighterConnection> 
            {
            public:
                using ReadHandler = std::function<void(const std::string&)>;
                using AcceptedHandler = std::function<void(std::shared_ptr<FighterConnection>)>;

            public:
                explicit FighterConnection(tcp::socket&& socket) :
                    m_webSocket(std::move(socket)),
                    m_isDisconnected(false)
                {
                }

                void start(AcceptedHandler handler);

                void requestAsync(const std::string& request, ReadHandler readHandler);
                
                inline bool isDisconnected() const
                {
                    return m_isDisconnected;
                }

            private:
                void acceptAsync(const beast::error_code& ec);
                void onWriteAsync(const beast::error_code& ec, std::size_t bytesWritten);
                void onReadAsync(const beast::error_code& ec, std::size_t bytesTransfered);
                void close();

            private:
                websocket::stream<tcp::socket> m_webSocket;
                beast::flat_buffer m_buffer;

                ReadHandler m_readHandler;
                AcceptedHandler m_acceptedHandler;

                bool m_isDisconnected;
            };

            using FighterConnectionPtr = std::shared_ptr<FighterConnection>;
        }
    }
}