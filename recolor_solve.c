#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_io.c"
#include "game_io.h"
#include "game.h"
#include "game.c"


void FIND_ONE (cgame g, char *filename ) {
    FILE * f = fopen(filename,"w");
    fprintf(f,"NO SOLUTION\n");
}

void NB_SOL (cgame g, char *filename) {
  FILE * f = fopen(filename,"w");
    fprintf(f,"NO SOLUTION\n");
}

void FIND_MIN (cgame g, char*filename) {
  FILE * f = fopen(filename,"w");
    fprintf(f,"NO SOLUTION\n");
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
