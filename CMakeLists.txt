#version minimale de cmake nécessaire
cmake_minimum_required(VERSION 3.3)
#nom du projet
project (recolor-text)
#positionne la variable

set(CMAKE_C_FLAGS "-std=c99 -Wall") ### options communes
set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG --coverage") ### options spécifiques
set(CMAKE_C_FLAGS_RELEASE "-O3") ### options spécifiques
#définit le nom du programme ainsi que 
#ses sources
add_executable(recolor_solve recolor_solve.c)
add_executable(recolor_text game.h game_io.h recolor_text.c)
#les dépendances sont calculées automatiquement

add_library(game_rand game_rand.c game_rand.h)
add_library(game game.c game_io.c)

target_link_libraries(recolor_text game game_rand)

# pkg-config --list-all  | grep -i sdl2
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMG REQUIRED SDL2_image)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)
set(SDL2_ALL_LIBS ${SDL2_LIBRARIES} ${SDL2_IMG_LIBRARIES} ${SDL2_TTF_LIBRARIES})
set(SDL2_ALL_INC ${SDL2_INCLUDE_DIRS} ${SDL2_IMG_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

include_directories(${SDL2_ALL_INC})
add_executable(recolor_sdl main.c recolor_sdl.c)
target_link_libraries(recolor_sdl ${SDL2_ALL_LIBS} m)


#Test ejin
include(CTest)
enable_testing()
add_test(test_game_new test_game_ejin new)
add_test(test_game_new_empty test_game_ejin newempty)
add_test(test_game_set_cell test_game_ejin setcell)
add_test(test_newext test_game_ejin newext)
add_executable(test_game_ejin test_game_ejin.c)

#Test zboumedris
add_test(test_game_set_max_moves test_game_zboumedris setmax)
add_test(test_game_nb_moves_max test_game_zboumedris nbmovesmax)
add_test(test_game_cell_current_color test_game_zboumedris cellcolor)
add_test(test_game_height test_game_zboumedris height)
add_executable(test_game_zboumedris test_game_zboumedris.c)

#Test lalanoix
add_test(test_game_restart test_game_lalanoix restart)
add_test(test_game_is_over test_game_lalanoix isover)
add_test(test_game_delete test_game_lalanoix delete)
add_test(test_iswrapping test_game_lalanoix iswrapping)
add_test(test_width test_game_lalanoix width)
add_test(test_gameload test_game_lalanoix load)
add_test(test_gamesave test_game_lalanoix save)
add_executable(test_game_lalanoix test_game_lalanoix.c)

#Test anouamani
add_test(test_nbmovescur test_game_anouamani nbmovescur)
add_test(test_playonemouve test_game_anouamani playonemove)
add_test(test_copy test_game_anouamani copy)
add_test(test_emptyext test_game_anouamani emptyext)
add_test(test_gamedef test_game_anouamani gamedef)
add_executable(test_game_anouamani test_game_anouamani.c)
