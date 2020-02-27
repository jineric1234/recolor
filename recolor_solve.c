#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_io.c"
#include "game_io.h"
#include "game.h"
#include "game.c"

int* tab_move(int x) {
    int *tab= malloc(sizeof(int)*x);
    if (tab==NULL){
        fprintf(stderr,"Error: solver tab Null\n");
        exit(EXIT_FAILURE);
    }
    tab[0]=0;
    for (uint i=1; i<x; i++){
        tab[i]=-1;
    }
    return tab;
}

int* tab_increment(int *tab, int size){
    tab[0]=tab[0]+1;
    for (uint i =0; i<size; i++){
        if(tab[i]==16){
            tab[i]=0;
            tab[i+1]=tab[i+1]+1;
        }
    }
    return tab;
}

bool end_moves(int *tab, int size){
    if (tab[size-1]==0){
        return false;
    }else{
        return true;
    }
}

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

void FIND_ONE (game g, char *filename ) {
    int size=(g->nbmax)+1;
    int *tab = tab_move(size);
    while(end_moves(tab, size)){
        uint i=0;
        while(tab[i]!=-1){
            game_play_one_move(g,tab[i]);
            i++;
        }
        if(game_is_over(g)){
            write_solution(filename,tab,i);
            break;
        }else{
            game_restart(g);
            tab_increment(tab,size);
        }
    }
    free(tab);
}

void NB_SOL (game g, char *filename) {
    //int tab = tab_move (1 + (g->nbmax));
    FILE * f = fopen(filename,"w");
    fprintf(f,"NO SOLUTION\n");
}

void FIND_MIN (game g, char*filename) {
    FIND_ONE (g,filename);
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
