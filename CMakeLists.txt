cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

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
	sources/application.cpp
	sources/gameState.cpp
	sources/introState.cpp
	sources/menuState.cpp
	sources/particles.cpp
	sources/state.cpp
	sources/stateMachine.cpp
	sources/resourceHolder.cpp
)

add_executable(Pong ${SOURCES})
target_link_libraries(Pong sfml-graphics sfml-audio)

# Install executable
install(TARGETS Pong
		RUNTIME DESTINATION .)

# Install game data
install(DIRECTORY media
		DESTINATION .)