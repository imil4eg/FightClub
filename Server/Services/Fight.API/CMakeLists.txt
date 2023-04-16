cmake_minimum_required(VERSION 3.10)

project(FightClub.Server.Fight.API)

add_compile_options(-Wall -Wextra -pedantic -Werror)

set(CMAKE_CXX_STANDARD 17)

include_directories(../Common/include/Network ../Common/include/Config ../Common/include ../Common/include/Models ../libs/json/include src src/Network src/Models src/Services src/Enums)

add_executable(FightClub.Server.Fight.API main.cpp src/Network/FighterConnection.cpp src/Network/FighterConnectionHandler.cpp src/Services/OpponentSearcher.cpp src/Services/FighterBuilder.cpp)

target_link_libraries(FightClub.Server.Fight.API FightClub.Server.Common)
