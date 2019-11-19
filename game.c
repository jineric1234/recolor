
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

/* typedef enum color_e {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    NB_COLORS
} color; */

struct game_s {
    color *cell; //pointe vers la grille du jeu
    color *cell_init; //pointe vers la grille du jeu initiale
    uint nbmax; // nombre max de move
    uint nbmovecur; //nombre de mouvements actuel
};

typedef const struct game_s *cgame;


game game_new(color *cells, uint nb_moves_max){
    game g=(game)malloc(sizeof(game));
    if (g==NULL){
        fprintf(stderr,"errrr");
        exit(1);
    }
    g->nbmax=nb_moves_max;
    g->nbmovecur=0;
    g->cell =(color*)malloc(SIZE*SIZE*sizeof(color));
     g->cell_init =(color*)malloc(SIZE*SIZE*sizeof(color));
     if (g->cell_init==NULL || g->cell==NULL){
         fprintf(stderr,"errror\n");
         exit(1);
     }
     for(int i=0;i<SIZE*SIZE;i++){
         g->cell[i]=cells[i];
         g->cell_init[i]=cells[i];
     }
    return g;
}


game game_new_empty(){
    game g=(game)malloc(sizeof(game));
    if (g==NULL){
        fprintf(stderr,"errrr\n");
        exit(1);
    }
    g->nbmax=12;
    g->nbmovecur=0;
    g->cell =(color*)malloc(SIZE*SIZE*sizeof(color));
     g->cell_init =(color*)malloc(SIZE*SIZE*sizeof(color));
     if (g->cell_init==NULL || g->cell==NULL){
         fprintf(stderr,"errror\n");
         exit(1);
     }
    return g;
}


void game_set_cell_init(game g, uint x, uint y, color c){
    
    
    }


void game_set_max_moves(game g, uint nb_max_moves){
    if (g==NULL || nb_max_moves==0){
        fprintf(stderr,"not enogh memory!\n");
        exit (EXIT_FAILURE);
    }
    
    g->nbmax = nb_max_moves;

}


uint game_nb_moves_max(cgame g){
     if (g==NULL){
        fprintf(stderr,"not enogh memory!\n");
        exit (EXIT_FAILURE);
    }
    
    return g->nbmax;
}


color game_cell_current_color(cgame g, uint x, uint y){
     if (g==NULL||x>=SIZE||y>=SIZE){
        fprintf(stderr,"not enogh memory!\n");
        exit (EXIT_FAILURE);
    }
    return  g->cell[(SIZE-y-1)*SIZE+x];
}


uint game_nb_moves_cur(cgame g){
    //tester g
    return g->nbmovecur;
}


void game_play_one_move(game g, color c){ return;}


game game_copy(cgame g){
    return NULL;
}


void game_delete(game g){return;}


bool game_is_over(cgame g){
    return false;
}


void game_restart(game g){return;}
