cmake_minimum_required(VERSION 3.10)

project(FightClub)

add_subdirectory(FightClub.Core)
add_subdirectory(FightClub)

target_link_libraries(FightClub)
