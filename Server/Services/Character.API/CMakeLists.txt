cmake_minimum_required(VERSION 3.10)

project(FightClub.Server.Character.API)

add_compile_options(-Wall -Wextra -pedantic -Werror)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 REQUIRED COMPONENTS Core Sql)

include_directories(${Qt5Core_INCLUDE_DIRS} ../Common/include/Network ../Common/include/Database ../Common/include/Config ../Common/include ../Common/include/Mediator ../Common/include/Models ../libs/json/include src/Network src/Database src/Enums src/Models src/Application/Queries src/Application/Commands)

add_executable(FightClub.Server.Character.API main.cpp src/Network/CharacterController.cpp src/Database/TableColumnsNames.cpp src/Application/Queries/InventoryQueries.cpp src/Application/Queries/ArmorQueries.cpp src/Application/Queries/WeaponQueries.cpp src/Application/Queries/CharacterQueries.cpp src/Application/Queries/AbilityQueries.cpp src/Application/Queries/AttributeQueries.cpp src/Application/Commands/CreateCharacterCommandHandler.cpp src/Application/Commands/UpdateCharacterCommandHandler.cpp)

target_link_libraries(FightClub.Server.Character.API FightClub.Server.Common)
