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
    FILE * f = fopen(filename,"w+");
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
    int *tab= calloc(x,sizeof(int));
    if (tab==NULL){
        fprintf(stderr,"Error: solver tab Null\n");
        exit(EXIT_FAILURE);
    }
    return tab;
}

int* tab_bool(int x) {
    int *tab= malloc(sizeof(bool)*x);
    if (tab==NULL){
        fprintf(stderr,"Error: solver tab Null\n");
        exit(EXIT_FAILURE);
    }
    for (uint i=1; i<x; i++){
        tab[i]=false;
    }
    return tab;
}

int* near_move(game g){
    if(g==NULL){
        fprintf(stderr,"game NULL\n");
        exit(EXIT_FAILURE);
    }
    int *tab = tab_bool(4);
    uint height = g->height;
    uint width = g->width;
    for (uint i=0; i<(height * width); i++){
        uint x = i%width;
        uint y = i/width;
        if (g->tab_bool[i]==true){
            if (y >= 1 && !g->tab_bool[i-width]) {
                uint c = g->cell[(y - 1) * game_width(g) + x];
                tab[c]=true;
            }
            // lower cell : (x,y+1)
            if (y + 1 < game_height(g) && !g->tab_bool[i+width]) {
                uint c = g->cell[(y + 1) * game_width(g) + x];
                tab[c] = true;
            }
            // left cell : (x-1,y)
            if (x >= 1 && !g->tab_bool[i-1]) {
                uint c = g->cell[y * game_width(g) + (x - 1)];
                tab[c] = true;
            }
            // right cell : (x+1,y)
            if (x + 1 < game_width(g) && !g->tab_bool[i+1]) {
                uint c = g->cell[y * game_width(g) + (x + 1)];
                tab[c] = true;
            }

            // if the game is wrapping, we check the other neighbors too
            if (game_is_wrapping(g)) {
                // (x,y) <=> y*game_width(g)+x
                // upper cell : (x,game_height(g)-1) <=> (game_height(g)-1)*game_width(g)+x)
                if (y == 0 && !g->tab_bool[(height - 1) * width + x]) {
                // color the cell and call function on its neighbors
                    uint c = g->cell[(game_height(g) - 1) * game_width(g) + x];
                    tab[c] = true;
                }
                // lower cell : (x,0) <=> x
                if ((y == game_height(g) - 1) && !g->tab_bool[x]) {
                    uint c = g->cell[x];
                    tab[c] = true;
                }
                // left cell : (game_width(g)-1,y) <=> y*game_width(g)+game_width(g)-1
                if (x == 0 && !g->tab_bool[i+width-1]) {
                    uint c = g->cell[y * game_width(g) + game_width(g) - 1];
                    tab[c] = true;
                }
                // right cell : (0,y) <=> y*game_width(g)
                if (x == game_width(g) - 1 && !g->tab_bool[i-width+1]) {
                    uint c = g->cell[y * game_width(g)];
                    tab[c] = true;
                }
            }
        }
    }
    return tab;
}


void solve_aux(game g, uint x, int *tabmove, char *filename ){
    int *tab = near_move(g);
    if (tab==NULL){
        fprintf(stderr,"tab NULL\n");
        exit(EXIT_FAILURE);
    }
    if (game_is_over(g)){
        write_solution(filename, tabmove, x);
        game_delete(g);
        free(tabmove);
        return;
    }
    if (g->nbmovecur > g->nbmax){
        game_delete(g);
        free(tabmove);
        return;
    }
    for (uint i = 0; i<=16; i++){
        if (tab[i]==true){
            game copy =  game_copy(g);
            game_play_one_move(copy,i);
            tabmove[x]=i;
            solve_aux(copy, x+1, tabmove, filename);
        }
    }
}

void FIND_ONE (game g, char *filename) {
    FILE * f = fopen(filename,"w+");
    fprintf(f, "FO");
    fclose(f);
}

void NB_SOL (game g, char *filename) {
    solve_aux(g, 0, tab_move(g->nbmax), filename);
    return;
}

void FIND_MIN (game g, char*filename) {
    FILE * f = fopen(filename,"w+");
    fprintf(f, "FM");
    fclose(f);
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
