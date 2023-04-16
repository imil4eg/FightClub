#include <iostream>

#include "ConfigParams.hpp"
#include "JsonConfigReader.hpp"
#include "UserRepository.hpp"

#include "ConnectionFactory.hpp"
#include "DatabaseQueryBuilder.hpp"
#include "UserController.hpp"
#include "OpenSSLPasswordHasher.hpp"

#include "HttpConnectionHandler.hpp"

#include "QueryExecutor.hpp"

namespace common = FightClub::Server::Common;
namespace user = FightClub::Server::User;

int main(int argc, char** argv)
{   
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <address> <port>\n"
                    << "For IPv4, try: receiver 0.0.0.0 80\n"
                    << "For IPv6, try: receiver 0::0 80\n";

        return EXIT_FAILURE;
    }

    const std::string address(argv[1]);
    const std::string port(argv[2]);

    common::JsonConfigReader reader("Config.json");
    common::JsonConfigReader rabbitConfigReader(common::ConfigParams::RabbitQueuesConfigPath);

    ConnectionFactory connectionFactory(reader.get(common::ConfigParams::DbConnectionString)->value);
    common::QueryExecutor queryExecutor(connectionFactory);
    user::UserRepository repository(queryExecutor);

    common::RequestProcesserContainer requestProcessersContainer;
    user::OpenSSLPasswordHasher passwordHasher;

    user::UserController userController(passwordHasher, repository, reader, requestProcessersContainer);

    boost::asio::io_service service(2);

    auto httpConnectionHandler = std::make_shared<common::HttpConnectionHandler>(service, address, port, requestProcessersContainer);
    httpConnectionHandler->run();

    return service.run();
}