#include <iostream>

#include "ConnectionFactory.hpp"
#include "ConfigParams.hpp"
#include "DatabaseQueryBuilder.hpp"
#include "JsonConfigReader.hpp"
#include "HttpConnectionHandler.hpp"

#include "CharacterController.hpp"

#include "AbilityQueries.hpp"
#include "AttributeQueries.hpp"
#include "ArmorQueries.hpp"
#include "CreateCharacterCommandHandler.hpp"
#include "CharacterQueries.hpp"
#include "InventoryQueries.hpp"
#include "UpdateCharacterCommandHandler.hpp"
#include "QueryExecutor.hpp"
#include "WeaponQueries.hpp"

namespace common = FightClub::Server::Common;
namespace character = FightClub::Server::Character;

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

    common::JsonConfigReader reader(common::ConfigParams::ConfigPath);
    
    ConnectionFactory connectionFactory(reader.get(common::ConfigParams::DbConnectionString)->value);
    common::QueryExecutor queryExecutor(connectionFactory);

    character::AbilityQueries abilityQueries(queryExecutor);
    character::AttributeQueries attributeQueries(queryExecutor);
    character::ArmorQueries armorQueries(queryExecutor, attributeQueries);
    character::WeaponQueries weaponQueries(queryExecutor);
    character::InventoryQueries inventoryQueries(armorQueries, weaponQueries); 
    character::CharacterQueries characterQueries(queryExecutor, inventoryQueries, attributeQueries, abilityQueries);

    common::Mediator mediator;

    auto createCharacterCommandHandler{std::make_shared<character::CreateCharacterCommandHandler>(queryExecutor)};
    mediator.registerHandler<character::CreateCharacterCommand>(createCharacterCommandHandler);

    auto updateCharacterCommandHandler{std::make_shared<character::UpdateCharacterCommandHandler>(queryExecutor)};
    mediator.registerHandler<character::UpdateCharacterCommand>(updateCharacterCommandHandler);

    common::RequestProcesserContainer requestProcesserContainer;
    character::CharacterController controller(characterQueries, mediator, requestProcesserContainer);

    boost::asio::io_service ioService(2);

    auto httpConnectionHandler = std::make_shared<common::HttpConnectionHandler>(ioService, address, port, requestProcesserContainer);
    httpConnectionHandler->run();

    return ioService.run();
}