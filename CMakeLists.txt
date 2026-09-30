cmake_minimum_required(VERSION 3.16)

project(text_rpg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GAME_SOURCES
  src/player.cpp
  src/enemy.cpp
  src/combat.cpp
  src/game.cpp
)

add_executable(text_rpg main.cpp ${GAME_SOURCES})
target_include_directories(text_rpg PRIVATE src)

enable_testing()

add_executable(game_tests tests/game_tests.cpp ${GAME_SOURCES})
target_include_directories(game_tests PRIVATE src)

add_test(NAME game_tests COMMAND game_tests)
