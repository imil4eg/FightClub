#include "ConfigParams.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            const std::string ConfigParams::RabbitQueuesConfigPath = "../Common/RabbitQueues.json";
            const std::string ConfigParams::ConfigPath = "Config.json";

            const std::string ConfigParams::RabbitConnectionString = "RabbitConnectionString";
            const std::string ConfigParams::RabbitUser = "RabbitUser";
            const std::string ConfigParams::RabbitPassword = "RabbitPassword";
            const std::string ConfigParams::RabbitQueue = "RabbitQueue";
            const std::string ConfigParams::RabbitRPCQueue = "RabbitRPCQueue";
            const std::string ConfigParams::RabbitExchange = "ApplicationExchange";
            const std::string ConfigParams::RabbitQueueRoutingKey = "RabbitQueueRoutingKey";
            
            const std::string ConfigParams::DbConnectionString = "DbConnectionString";
            const std::string ConfigParams::DbTableName = "DbTableName";

            const std::string ConfigParams::UserQueue = "UserQueue"; 
            const std::string ConfigParams::UserRPCQueue = "UserRPCQueue";
            const std::string ConfigParams::UserExchange = "UserExchange";
            const std::string ConfigParams::CharacterQueue = "CharacterQueue";
            const std::string ConfigParams::CharacterRPCQueue = "CharacterRPCQueue";
            const std::string ConfigParams::CharacterExchange = "CharacterExchange";

            const std::string ConfigParams::JWT::Issuer = "JWTIssuer";
            const std::string ConfigParams::JWT::Type = "JWTType";
            const std::string ConfigParams::JWT::PayloadClaimID = "JWTPayloadClaimID";
            const std::string ConfigParams::JWT::Claim = "JWTClaim";
            const std::string ConfigParams::JWT::Key = "JWTKey";
        }
    }
}