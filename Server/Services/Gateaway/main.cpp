#include <iostream>

#include "BoostCommon.hpp"

#include "ConnectionHandler.hpp"
#include "JsonConfigReader.hpp"

namespace common = FightClub::Server::Common;
namespace gateaway = FightClub::Server::Gateaway;

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

    boost::asio::io_service ioService(2);
    
    common::JsonConfigReader servicesConfig("Services.json");
    gateaway::ServicesContainer container(servicesConfig);
    common::JsonConfigReader mainConfig("Config.json");
    auto handler = std::make_shared<gateaway::ConnectionHandler>(ioService, address, port, container, mainConfig);

    handler->run();

    return ioService.run();
}