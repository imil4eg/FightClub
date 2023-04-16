cmake_minimum_required(VERSION 3.10)

project(API.Test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 REQUIRED COMPONENTS Core Network)
find_package(Boost 1.75.0 REQUIRED COMPONENTS system filesystem thread)

include_directories(${Qt5Core_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ../libs/json/include)

link_directories(${Boost_LIBRARY_DIRS})

add_executable(API.Test main.cpp)

target_link_libraries(API.Test Qt5::Core Qt5::Network ${Boost_LIBRARIES})
