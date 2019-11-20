#version minimale de cmake nécessaire
cmake_minimum_required(VERSION 3.3)
#nom du projet
project (recolor-text)
#positionne la variable
set(CMAKE_C_FLAGS "-std=c99 -g -Wall")
#définit le nom du programme ainsi que 
#ses sources
add_executable(recolor_text game.h game_io.h recolor_text.c)
#les dépendances sont calculées automatiquement

add_library(game game.c game_io.c)

target_link_libraries(recolor_text game)


#Tests

add_executable(test_game_ejin test_game_ejin.c)
add_executable(test_game_lalanoix test_game_lalanoix.c)
add_executable(test_game_zboumedris test_game_zboumedris.c)
add_executable(test_game_anouamani test_game_anouamani.c)
