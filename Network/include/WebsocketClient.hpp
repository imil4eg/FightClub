#pragma once

#include "BaseConnectionClient.hpp"

namespace FightClub::Network 
{
    class WebsocketClient : private ConnectionClient
    {
    public:
        using websocket_stream = websocket::stream<beast::tcp_stream>; 

    public:
        WebsocketClient(net::io_service& ios, const std::string& host, const std::string& port) :
            ConnectionClient(ios, host, port),
            websocket_{net::make_strand(ios)}
        {
        }

        TaskWithError ConnectAsync();
        TaskWithError WriteAsync(RequestData&& request_data);
        ReadTask ReadAsync();
        TaskWithError CloseAsync();
    
    protected:
        beast::tcp_stream& GetStream() override {
            return beast::get_lowest_layer(websocket_);
        }

    private:
        websocket_stream websocket_;
    };
}