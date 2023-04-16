cmake_minimum_required(VERSION 3.10)

project(FightClub.Server.Gateaway)

add_compile_options(-Wall -Wextra -pedantic -Werror)

set(CMAKE_CXX_STANDARD 17)

include_directories(src ../libs/json/include ../libs/jwt-cpp/include ../Common/include/Network ../Common/include ../Common/include/Config)

add_executable(FightClub.Server.Gateaway main.cpp src/Connection.cpp src/ConnectionHandler.cpp)

target_link_libraries(FightClub.Server.Gateaway FightClub.Server.Common)
