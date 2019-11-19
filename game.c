
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "game_io.h"
#define SIZE 12



color cell_init[]= {
        0,0,0,2,0,2,1,0,1,0,3,0,
        0,3,3,1,1,1,1,3,2,0,1,0,
        1,0,1,2,3,2,3,2,0,3,3,2,
        2,3,1,0,3,2,1,1,1,2,2,0,
        2,1,2,3,3,3,3,2,0,1,0,0,
        0,3,3,0,1,1,2,3,3,2,1,3,
        1,1,2,2,2,0,0,1,3,1,1,2,
        1,3,1,3,1,0,1,0,1,3,3,3,
        0,3,0,1,0,0,2,1,1,1,3,0,
        1,3,1,0,0,0,3,2,3,1,0,0,
        1,3,3,1,1,2,2,3,2,0,0,2,
        2,0,2,3,0,1,1,1,2,3,0,1
};


color cell[]= {
        0,0,0,2,0,2,1,0,1,0,3,0,
        0,3,3,1,1,1,1,3,2,0,1,0,
        1,0,1,2,3,2,3,2,0,3,3,2,
        2,3,1,0,3,2,1,1,1,2,2,0,
        2,1,2,3,3,3,3,2,0,1,0,0,
        0,3,3,0,1,1,2,3,3,2,1,3,
        1,1,2,2,2,0,0,1,3,1,1,2,
        1,3,1,3,1,0,1,0,1,3,3,3,
        0,3,0,1,0,0,2,1,1,1,3,0,
        1,3,1,0,0,0,3,2,3,1,0,0,
        1,3,3,1,1,2,2,3,2,0,0,2,
        2,0,2,3,0,1,1,1,2,3,0,1
};

typedef unsigned int uint;

typedef enum color_e {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    NB_COLORS
} color;

typedef struct game_s {
    color *cell; //pointe vers la grille du jeu
    color *cell_init //pointe vers la grille du jeu initiale
    uint nbmax; // nombre max de move
    uint nbmovecur; //nombre de mouvements actuel
}game;

typedef const struct game_s *cgame;


game game_new(color *cells, uint nb_moves_max){
    return NULL;
}


game game_new_empty(){
    return NULL;
}


void game_set_cell_init(game g, uint x, uint y, color c);{}


void game_set_max_moves(game g, uint nb_max_moves){
    g.nbmax = nb_max_moves;
}


uint game_nb_moves_max(cgame g){
    return g.nbmax;
}


color game_cell_current_color(cgame g, uint x, uint y){
    return g.cell[x][y];
}


uint game_nb_moves_cur(cgame g){
    return 0;
}


void game_play_one_move(game g, color c){}


game game_copy(cgame g){
    return g;
}


void game_delete(game g){}


bool game_is_over(cgame g){
    return false;
}


void game_restart(game g){}
