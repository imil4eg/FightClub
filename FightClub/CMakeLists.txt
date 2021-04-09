cmake_minimum_required(VERSION 3.10)

project(FightClub)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.75.0)

include_directories(${Boost_INCLUDE_DIRS} ../FightClub.Core/include Headers libs)

link_directories(${Boost_LIBRARY_DIRS})

add_executable(FightClub FightClub.cpp Menu.cpp IO/CommandLineParser.cpp CharacterStuff/AbilitiesDisplayer.cpp CharacterStuff/AttributesManager.cpp CharacterStuff/CharacterCustomizerMenu.cpp CharacterStuff/AbilitiesManager.cpp CharacterStuff/CharacterCustomizer.cpp CharacterStuff/InventoryManager.cpp)

target_link_libraries(FightClub ${Boost_LIBRARIES} FightClub.Core)
