#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_io.c"
#include "game_io.h"
#include "game.h"
#include "game.c"

void write_solution(char *filename,int *tab, int size_tab){
    FILE * f = fopen(filename,"w");
    for(uint i = 0; i<=size_tab; i++){
        uint v = tab[i];
        if (v>=0 && v<=9){fprintf(f,"%u ",v);}
        if (v==10){fprintf(f,"A ");}
        if (v==11){fprintf(f,"B ");}
        if (v==12){fprintf(f,"C ");}
        if (v==13){fprintf(f,"D ");}
        if (v==14){fprintf(f,"E ");}
        if (v==15){fprintf(f,"F ");}
    }
    fprintf(f,"\n");
    fclose(f);
}



int* tab_move(int x) {
    int *tab= malloc(sizeof(int)*x);
    if (tab==NULL){
        fprintf(stderr,"Error: solver tab Null\n");
        exit(EXIT_FAILURE);
    }
    for (uint i=1; i<x; i++){
        tab[i]=-1;
    }
    return tab;
}

int* near_move(game g){
    int *tab = tab_move(16);
    uint height = g-> heigth;
    uint width = g->width;
    for (uint i=0; i<(height * width); i++){
        uint x = i%width;
        uint y = i
        if (g->tab_init[i]=true){
            if (y >= 1 && game_cell_current_color(g, x, y - 1) == c_old) {
                // color the cell and call function on its neighbors
                g->cell[(y - 1) * game_width(g) + x] = c_new;
            }
            // lower cell : (x,y+1)
            if (y + 1 < game_height(g) && game_cell_current_color(g, x, y + 1) == c_old) {
                g->cell[(y + 1) * game_width(g) + x] = c_new;
            }
            // left cell : (x-1,y)
            if (x >= 1 && game_cell_current_color(g, x - 1, y) == c_old) {
                g->cell[y * game_width(g) + (x - 1)] = c_new;
            }
            // right cell : (x+1,y)
            if (x + 1 < game_width(g) && game_cell_current_color(g, x + 1, y) == c_old) {
                g->cell[y * game_width(g) + (x + 1)] = c_new;
            }

            // if the game is wrapping, we check the other neighbors too
            if (game_is_wrapping(g)) {
                // (x,y) <=> y*game_width(g)+x
                // upper cell : (x,game_height(g)-1) <=> (game_height(g)-1)*game_width(g)+x
                if (y == 0 && game_cell_current_color(g, x, game_height(g) - 1) == c_old) {
                // color the cell and call function on its neighbors
                g->cell[(game_height(g) - 1) * game_width(g) + x] = c_new;
                }
                // lower cell : (x,0) <=> x
                if (y == game_height(g) - 1 && game_cell_current_color(g, x, 0) == c_old) {
                g->cell[x] = c_new;
                }
                // left cell : (game_width(g)-1,y) <=> y*game_width(g)+game_width(g)-1
                if (x == 0 && game_cell_current_color(g, game_width(g) - 1, y) == c_old) {
                g->cell[y * game_width(g) + game_width(g) - 1] = c_new;
                }
                // right cell : (0,y) <=> y*game_width(g)
                if (x == game_width(g) - 1 && game_cell_current_color(g, 0, y) == c_old) {
                g->cell[y * game_width(g)] = c_new;
                }
            }
            return;
        }
    }
    return tab;
}


void FIND_ONE (game g, char *filename) {
}

void NB_SOL (game g, char *filename) {

}

void FIND_MIN (game g, char*filename) {
    exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[]){
    if(argc==4){
        if (strcmp("FIND_ONE", argv[1]) == 0){
            game g = game_load(argv[2]);
            char *sol= strcat (argv[3],".sol");
            FIND_ONE(g,sol);
        }
        if (strcmp("NB_SOL", argv[1]) == 0){
            game g = game_load(argv[2]);
            char *sol= strcat (argv[3],".nbsol");
           NB_SOL(g,sol);
        }
        if (strcmp("FIND_MIN", argv[1]) == 0){
            game g = game_load(argv[2]);
            char *sol= strcat (argv[3],".sol");
            FIND_MIN(g,sol);
        }
    }
}
