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


#Test ejin
enable_testing()
add_test(test_game_new test_game_ejin new)
add_test(test_game_new_empty test_game_ejin newempty)
add_test(test_game_set_cell test_game_ejin setcell)

add_executable(test_game_ejin test_game_ejin.c)

#Test zboumedris
add_test(test_game_set_max_moves test_game_zboumedris setmax)
add_test(test_game_nb_moves_max test_game_zboumedris nbmovesmax)
add_test(test_game_cell_current_color test_game_zboumedris cellcolor)

add_executable(test_game_zboumedris test_game_zboumedris.c)

#Test lalanoix
add_test(test_game_restart test_game_lalanoix restart)
add_test(test_game_is_over test_game_lalanoix isover)
add_test(test_game_delete test_game_lalanoix delete)
add_executable(test_game_lalanoix test_game_lalanoix.c)

#Test anouamani
add_test(test_nbmovescur test_game_anouamani nbmovescur)
add_test(test_playonemouve test_game_anouamani playonemove)
add_test(test_copy test_game_anouamani copy)
add_executable(test_game_anouamani test_game_anouamani.c)
