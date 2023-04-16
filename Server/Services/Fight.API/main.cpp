#include <iostream>
#include <string>

#include "BoostCommon.hpp"
#include "ConfigParams.hpp"
#include "FighterBuilderFactory.hpp"
#include "FighterConnectionHandler.hpp"
#include "JsonConfigReader.hpp"
#include "OpponentSearcher.hpp"

namespace common = FightClub::Server::Common;
namespace fight = FightClub::Server::Fight;

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

    common::JsonConfigReader jsonConfigReader(common::ConfigParams::ConfigPath);
    fight::OpponentSearcher opponentSearcher;

    boost::asio::io_service ioService(2);

    fight::FighterBuilderFactory fighterBuilderFactory(jsonConfigReader, ioService);

    auto connectionHandler = std::make_shared<fight::FighterConnectionHandler>(ioService, address, port, 
                                                                                fighterBuilderFactory, opponentSearcher);
    connectionHandler->run();

    return ioService.run();
}