set (CMAKE_CXX_STANDARD  11)
cmake_minimum_required(VERSION 3.1)

project(evil-pipe)

file(GLOB evil-pipe-sources
        ${PROJECT_SOURCE_DIR}/src/server/*.cpp
        ${PROJECT_SOURCE_DIR}/src/session/*.cpp
        ${PROJECT_SOURCE_DIR}/src/main.cpp
        )


add_executable(evil-pipe ${evil-pipe-sources})
target_sources(evil-pipe PUBLIC ${evil-pipe-sources})
target_include_directories(evil-pipe PUBLIC ${PROJECT_SOURCE_DIR}/include)

find_package(Boost REQUIRED system thread filesystem)
include_directories(${BOOST_INCLUDE_DIRS})

target_link_libraries(evil-pipe ${Boost_LIBRARIES})
