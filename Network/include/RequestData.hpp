#pragma once

#include "BoostCommon.hpp"
#include "JsonDefinitions.hpp"

namespace FightClub::Network
{
    class RequestData
    {
    public:
        using Ptr = std::unique_ptr<RequestData>;

    public:
        std::string target;
        std::string token;
        http::verb method;
        json body;
        std::string IP;
        std::string port;
    };
}