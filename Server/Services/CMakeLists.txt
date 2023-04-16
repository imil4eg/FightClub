cmake_minimum_required(VERSION 3.10)

add_compile_options(-g)

project(Services)

add_subdirectory(libs)

add_subdirectory(API.Test)

add_subdirectory(Common)
add_subdirectory(User.API)
add_subdirectory(Character.API)
add_subdirectory(Fight.API)
add_subdirectory(Gateaway)
