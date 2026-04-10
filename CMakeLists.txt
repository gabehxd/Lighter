# Minimum CMake version required, we'll just use the latest version.
cmake_minimum_required(VERSION 3.22)
# Project name, version and description
project(lighter VERSION 1.0 DESCRIPTION "LighterWise Discord bot")

	 
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Werror
    )
	 
# Create an executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/commands/Command.cpp
    src/commands/Ping.cpp
    src/events/CommandEvent.cpp
    src/events/VerifyEvent.cpp
    src/commands/Role.cpp
    src/utils.cpp
    src/events/HelloEvent.cpp
    src/commands/Info.cpp
    src/commands/ChromeCount.cpp
)
	 
# Find our pre-installed DPP package (using FindDPP.cmake).
find_package(DPP REQUIRED)
	 
# Link the pre-installed DPP package.
target_link_libraries(${PROJECT_NAME} 
    ${DPP_LIBRARIES}
)
	 
# Include the DPP directories.
target_include_directories(${PROJECT_NAME} PRIVATE
    ${DPP_INCLUDE_DIR}
)
	 
# Set C++ version
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)