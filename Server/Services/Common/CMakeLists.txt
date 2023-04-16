cmake_minimum_required(VERSION 3.10)

project(FightClub.Server.Common)

add_compile_options(-Wall -Wextra -pedantic -Werror)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Boost 1.75.0 REQUIRED COMPONENTS system filesystem thread)

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

include_directories(${Qt5Core_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} src include/Database include/Network include/Config ../libs/json/include include include/Mediator include/Models)

link_directories(${Boost_LIBRARY_DIRS})

add_library(FightClub.Server.Common STATIC src/Database/ConnectionFactory.cpp src/Database/QueryExecutor.cpp src/Database/QueryParamHolder.cpp src/Database/DatabaseQueryBuilder.cpp src/Database/DatabaseQueryDictionary.cpp src/Network/BoostCommon.cpp src/Config/ConfigParams.cpp src/Config/JsonConfigReader.cpp src/Network/RequestProcesserContainer.cpp src/Network/HttpStatuses.cpp src/Network/JsonAttributes.cpp src/Network/BaseController.cpp src/Network/Request.cpp src/Network/NetworkMessage.cpp src/Network/BaseConnectionHandler.cpp src/Network/HttpConnectionHandler.cpp src/Network/HttpConnection.cpp src/Network/HttpClient.cpp src/Models/ModelToJsonMapper.cpp src/Models/CharacterModel.cpp)

target_link_libraries(FightClub.Server.Common Qt5::Core Qt5::Sql ${Boost_LIBRARIES})
