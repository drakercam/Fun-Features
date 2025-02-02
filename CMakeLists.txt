cmake_minimum_required(VERSION 3.10)
project(MyGameProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML
find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics window system audio)
include_directories(${SFML_INCLUDE_DIR})

# Add all source files
set(SOURCES
    main.cpp
    game.cpp
    menu.cpp
    timer.cpp
    game_object.cpp
    enemy_game_object.cpp
    player_game_object.cpp
)

set(HEADERS
    game.h
    bullet.h
    menu.h
    timer.h
    game_object.h
    enemy_game_object.h
    player_game_object.h
)

# Create executable
add_executable(game ${SOURCES} ${HEADERS})

# CMakeLists.txt
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/textures
        $<TARGET_FILE_DIR:game>/textures
)

# Link SFML libraries
target_link_libraries(game PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
