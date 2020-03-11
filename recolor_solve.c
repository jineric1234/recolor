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

int couleur_tab(game g){
    if (g==NULL){
        exit(EXIT_FAILURE);
    }
    int v = 0;
    for(uint i=0; i<(g->width * g->height); i++){
        if (g->cell[i]>v){
            v=g->cell[i];
        }
    }
    return v;
}

void write_solution1(FILE *f,int *tab, int size_tab, int *x, int *a){
    if (tab==NULL || f==NULL){
        fprintf(stderr, "erreur pointeur null\n");
        exit(EXIT_FAILURE);
    }
    for(uint i = 0; i<size_tab; i++){
        uint v = tab[i];
        a[i]=v;

    }
    x[0]=size_tab;
    fprintf(f,"\n");
}

void write_solution2(int *tab, int size_tab, int *v, int *a, int *m){
    if (tab==NULL){
        fprintf(stderr, "erreur pointeur null\n");
        exit(EXIT_FAILURE);
    }
    if (size_tab<=m[0]){
        for(uint i = 0; i<size_tab; i++){
            uint v = tab[i];
            a[i]=v;
        }
        m[0]=size_tab;
    }
    v[0]=1;
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
                if ((y == height - 1) && !g->tab_bool[x]){
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

void solve_aux(game g, uint x, int *tabmove, uint z, int *v){
    if (game_is_over(g)){
        game_delete(g);
        v[0]=v[0]+1;
    }
    else{
        if (x > (g->nbmax)){
            game_delete(g);
        }
        bool *tab = near_move(g,z);
        if (tab==NULL){
            fprintf(stderr,"tab NULL\n");
            exit(EXIT_FAILURE);
        }
        for (uint i = 0; i<z; i++){
            if (tab[i]==true){
                game copy =  game_copy(g);
                game_play_one_move(copy,i);
                tabmove[x]=i;
                solve_aux(copy, x+1, tabmove, z, v);
            }
        }
    }
}

void solve_aux1(game g, uint x, int *tabmove, FILE *filename, uint z, int *v, int*a){
    if (x > (g->nbmax)){
        game_delete(g);
        return;
    }
    if (game_is_over(g)){
        write_solution1(filename, tabmove, x, v, a);
        game_delete(g);
        return;
    }
    bool *tab = near_move(g,z);
    if (tab==NULL){
        fprintf(stderr,"tab NULL\n");
        exit(EXIT_FAILURE);
    }
    else{
        if (v[0]==1 || x>(g->nbmax)){
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
                    solve_aux1(copy, x+1, tabmove1, filename, z, v, a);
                }
            }
        }
    }
    game_delete(g);
}

void solve_aux2(game g, uint x, int *tabmove, uint z, int *v, int*a, int *m){
    if (x > (g->nbmax)){
        game_delete(g);
    }
    else if (game_is_over(g)){
        write_solution2(tabmove, x, v, a, m);
        game_delete(g);
    }
    else{
        bool *tab = near_move(g,z);
        if (tab==NULL){
            fprintf(stderr,"tab NULL\n");
            exit(EXIT_FAILURE);
        }
        for (uint i = 0; i<z; i++){
            if (tab[i]==true){
                game copy =  game_copy(g);
                game_play_one_move(copy,i);
                tabmove[x]=i;
                solve_aux2(copy, x+1, tabmove, z, v, a, m);
            }
        }
    }
}

void FIND_ONE (game g, char *filename) {
    FILE * f = fopen(filename,"w+");
    color c = game_cell_current_color(g,0,0);
    int *v=(int*)malloc(sizeof(int)*1);
    int *a=(int*)malloc((g->nbmax)*sizeof(int));
    v[0]=0;
    game_play_one_move(g,c);
    solve_aux1(g, 0, tab_move(g->nbmax), f, 16, v, a);
    fclose(f);
    if (v[0]==0){
        FILE * f = fopen(filename,"w+");
        fprintf(f, "NO SOLUTION");
        fclose(f);
    }else{
        FILE * f = fopen(filename,"w+");
        uint m = v[0];
        for(uint i = 0; i<m; i++){
            uint v = a[i];
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
    free(v);
    free(a);
}

void NB_SOL (game g, char *filename){
    color c = game_cell_current_color(g,0,0);
    game_play_one_move(g,c);
    int* tabmove = tab_move(g->nbmax);
    int* v=(int*)malloc(sizeof(int)*1);
    int m= couleur_tab(g) + 1;
    v[0]=0;
    solve_aux(g, 0, tabmove, m ,v);
    if (v[0]==0){
        FILE * f = fopen(filename,"w+");
        fprintf(f, "NO SOLUTION\n");
        fclose(f);
    }else{
        FILE * f = fopen(filename,"w+");
        fprintf(f, "NB_SOL = %d\n", v[0]);
        fclose(f);
    }
    free(v);
    return;
}

void FIND_MIN (game g, char*filename) {
    int *v=(int*)malloc(sizeof(int)*1); //if we found a solution
    int *m=(int*)malloc(sizeof(int)*1); //size of the solution
    int *a=(int*)malloc((g->nbmax)*sizeof(int)); //tab with the final solution
    m[0]=g->nbmax;
    v[0]=0;
    color c = game_cell_current_color(g,0,0);
    game_play_one_move(g,c);
    int* tabmove = tab_move(g->nbmax);
    solve_aux2(g, 0, tabmove, 16, v, a, m);
    if (v[0]==0){
        FILE * f = fopen(filename,"w+");
        fprintf(f, "NO SOLUTION\n");
        fclose(f);
    }else{
        FILE * f = fopen(filename,"w+");
        for(uint i = 0; i<m[0]; i++){
            uint v = a[i];
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
    free(m);
    free(tabmove);
    free(v);
    free(a);
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
