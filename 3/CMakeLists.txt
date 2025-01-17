# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(Zasada)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

find_package(X11 REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/game_code
    /usr/include/nlohmann # Include nlohmann/json headers
)

file(GLOB GAME_CODE_SOURCES "game_code/*.cpp")

# Add the executable
add_executable(Zasada LoadoutWindow.cpp TextField.cpp main.cpp ${GAME_CODE_SOURCES})

# Link SFML libraries
target_link_libraries(Zasada sfml-graphics sfml-window sfml-system ${X11_LIBRARIES})

set_target_properties(Zasada PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# Copy resources to the build directory
file(COPY Sprites mission_config.json  DESTINATION ${CMAKE_BINARY_DIR})
# file(COPY mission_config.json $(CMAKE_BINARY_DIR))
add_custom_target(run
    COMMAND Zasada
    DEPENDS Zasada
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Zasada..."
)