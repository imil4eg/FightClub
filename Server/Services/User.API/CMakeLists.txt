cmake_minimum_required(VERSION 3.10)

project(FightClub.Server.User.API)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_compile_options(-Wall -Wextra -pedantic -Werror)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 REQUIRED COMPONENTS Core Sql)
find_package(OpenSSL REQUIRED)

include_directories(${Qt5Core_INCLUDE_DIRS} src/Network ../Common/include/Network ../Common/include/Database ../Common/include/Config src/Models src/Repositories ../libs/json/include src/Controllers ../libs/jwt-cpp/include src/PasswordHashers ../Common/include)

add_executable(FightClub.Server.User.API main.cpp src/Repositories/UserRepository.cpp src/Repositories/TableColumnsName.cpp src/Controllers/UserController.cpp src/PasswordHashers/OpenSSLPasswordHasher.cpp)

target_link_libraries(FightClub.Server.User.API FightClub.Server.Common Qt5::Core Qt5::Sql OpenSSL::Crypto)
