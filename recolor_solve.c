#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "game_io.c"
#include "game_io.h"
#include "game.h"
#include "game.c"

int testSiFichierVide(FILE* fichier){
    int caracterePremier = 0;
 
    //On lit le prmeier caractère du fichier
    caracterePremier = fgetc(fichier);
    if(caracterePremier==EOF)
    {
        return 1;//le fichier est vide donc on retourne 1
    }
    return 0;//le fichier n'est pas vide donc on retourne 0
}

void write_solution(FILE *f,int *tab, int size_tab){
    if (tab==NULL || f==NULL){
        fprintf(stderr, "erreur pointeur null\n");
        exit(EXIT_FAILURE);
    }
    
    for(uint i = 0; i<size_tab; i++){
        uint v = tab[i];
        printf("%d",v);
        if (v>=0 && v<=9){fprintf(f,"%u ",v);}
        if (v==10){fprintf(f,"A ");}
        if (v==11){fprintf(f,"B ");}
        if (v==12){fprintf(f,"C ");}
        if (v==13){fprintf(f,"D ");}
        if (v==14){fprintf(f,"E ");}
        if (v==15){fprintf(f,"F ");}
    }
    fprintf(f,"\n");
    printf("\n");
    
}

int* tab_move(int x) {
    int *tab= (int*)malloc(x * sizeof(int));
    if (tab==NULL){
        fprintf(stderr,"Error: solver tab Null\n");
        exit(EXIT_FAILURE);
    }
    return tab;
}

bool* tab_bool1(int x) {
    bool *tab= (bool*)malloc(sizeof(bool) * x);
    if (tab==NULL){
        fprintf(stderr,"Error: solver tab Null\n");
        exit(EXIT_FAILURE);
    }
    for (uint i=0; i<x; i++){
        tab[i]=false;
    }
    return tab;
}

bool* near_move(game g, uint z){
    if(g==NULL){
        fprintf(stderr,"game NULL\n");
        exit(EXIT_FAILURE);
    }
    bool *tab = tab_bool1(z);
    uint height = g->height;
    uint width = g->width;
    for (uint i=0; i<(height * width); i++){
        uint x = i%width;
        uint y = i/width;
        if (g->tab_bool[i]==true){
            // upper cell : (x,y-1)
            if (y >= 1 && !g->tab_bool[i-width]) {
                uint c = g->cell[(y - 1) * width + x];
                tab[c]=true;
            }
            // lower cell : (x,y+1)
            if (y + 1 < height && !g->tab_bool[i+width]) {
                uint c = g->cell[(y + 1) * width + x];
                tab[c] = true;
            }
            // left cell : (x-1,y)
            if (x >= 1 && !g->tab_bool[i-1]) {
                uint c = g->cell[y * width + (x - 1)];
                tab[c] = true;
            }
            // right cell : (x+1,y)
            if (x + 1 < width && !g->tab_bool[i+1]) {
                uint c = g->cell[y * width + (x + 1)];
                tab[c] = true;
            }

            // if the game is wrapping, we check the other neighbors too
            if (game_is_wrapping(g)) {
                // (x,y) <=> y*game_width(g)+x
                // upper cell : (x,game_height(g)-1) <=> (game_height(g)-1)*game_width(g)+x)
                if (y == 0 && !g->tab_bool[(height - 1) * width + x]) {
                // color the cell and call function on its neighbors
                    uint c = g->cell[(height - 1) * width + x];
                    tab[c] = true;
                }
                // lower cell : (x,0) <=> x
                if ((y == height - 1) && !g->tab_bool[x]) {
                    uint c = g->cell[x];
                    tab[c] = true;
                }
                // left cell : (game_width(g)-1,y) <=> y*game_width(g)+game_width(g)-1
                if (x == 0 && !g->tab_bool[i+width-1]) {
                    uint c = g->cell[y * width + width - 1];
                    tab[c] = true;
                }
                // right cell : (0,y) <=> y*game_width(g)
                if (x == width - 1 && !g->tab_bool[i-width+1]) {
                    uint c = g->cell[y * width];
                    tab[c] = true;
                }
            }
        }
    }
    return tab;
}



void solve_aux(game g, uint x, int *tabmove, FILE *filename, uint z ){
    if (x > (g->nbmax)){
        game_delete(g);
        free(tabmove);
        return;
    }
    if (game_is_over(g)){
        write_solution(filename, tabmove, x);
        game_delete(g);
        free(tabmove);
        return;
    }
    bool *tab = near_move(g,z);
    if (tab==NULL){
        fprintf(stderr,"tab NULL\n");
        exit(EXIT_FAILURE);
    }
    else{
        if (x>(g->nbmax)){
            game_delete(g);
            free(tab);
        }else{
            for (uint i = 0; i<z; i++){
                if (tab[i]==true){
                    game copy =  game_copy(g);
                    game_play_one_move(copy,i);
                    int* tabmove1= tab_move((g->nbmax));
                    for (uint y=0; y<(g->nbmax); y++){
                        tabmove1[y]=tabmove[y];
                    }
                    tabmove1[x]=i;
                    solve_aux(copy, x+1, tabmove1, filename, z);
                }
            }
        }
    }
    game_delete(g);
}

void FIND_ONE (game g, char *filename) {
    FILE * f = fopen(filename,"w+");
    fprintf(f, "FO");
    fclose(f);
}

void NB_SOL (game g, char *filename) {
    FILE * f = fopen(filename,"w+");
    color c = game_cell_current_color(g,0,0);
    game_play_one_move(g,c);
    solve_aux(g, 0, tab_move(g->nbmax), f, 10);
    fclose(f);
    uint v = testSiFichierVide(f);
    if (v==1){
        FILE * f = fopen(filename,"w+");
        fprintf(f,"NO SOLUTION");
        fclose(f);
    }
    
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
