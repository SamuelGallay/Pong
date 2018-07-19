cmake_minimum_required(VERSION 3.1)

project(Pong)

if(MSVC)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(SFML_STATIC_LIBRARIES TRUE)
endif(MSVC)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

include_directories(headers/)

set(
	SOURCES
	sources/main.cpp
	sources/game.cpp
	sources/particles.cpp
)

add_executable(Pong ${SOURCES})
target_link_libraries(Pong sfml-graphics sfml-audio)