#pragma once

#include <string>

namespace FightClub {
    namespace Server {
        namespace Common {

            class ConfigParams
            {
            public:
                static const std::string RabbitQueuesConfigPath;
                static const std::string ConfigPath;

                static const std::string RabbitConnectionString;
                static const std::string RabbitUser;
                static const std::string RabbitPassword;
                static const std::string RabbitQueue;
                static const std::string RabbitRPCQueue;
                static const std::string RabbitExchange;
                static const std::string RabbitQueueRoutingKey;   

                static const std::string DbConnectionString;
                static const std::string DbTableName;

                class JWT
                {
                public:
                    static const std::string Token;
                    static const std::string Issuer;
                    static const std::string Type;
                    static const std::string PayloadClaimID;
                    static const std::string Claim;
                    static const std::string Key;

                    JWT() = delete;
                    ~JWT() = delete;
                };

                static const std::string UserQueue;
                static const std::string UserRPCQueue;
                static const std::string UserExchange;
                static const std::string CharacterQueue;
                static const std::string CharacterRPCQueue;
                static const std::string CharacterExchange;

                ConfigParams() = delete;
                ~ConfigParams() = delete;
            };
        }
    }
}