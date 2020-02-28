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
    int *tab = tab_move(15);
    return tab;

}






void FIND_ONE (game g, char *filename) {
}

void NB_SOL (game g, char *filename) {
    //int tab = tab_move (1 + (g->nbmax));
    FILE * f = fopen(filename,"w");
    fprintf(f,"NO SOLUTION\n");
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
