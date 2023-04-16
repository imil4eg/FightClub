cmake_minimum_required(VERSION 3.10)

project(${CMAKE_PROJECT_NAME}.Network)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-fcoroutines)

find_package(Boost 1.75.0 REQUIRED COMPONENTS system filesystem thread)

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

include_directories(${Boost_INCLUDE_DIRS})

link_directories(${Boost_LIBRARY_DIRS})

add_library(${PROJECT_NAME} STATIC
	src/BaseConnectionClient.cpp
	src/HttpClient.cpp 
	src/WebsocketClient.cpp
)

target_include_directories(${PROJECT_NAME} 
	INTERFACE include/
	PUBLIC ${CMAKE_SOURCE_DIR}/libs/json/include
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
