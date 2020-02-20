#ifndef GAME_IO_H
#define GAME_IO_H
#include <stdio.h>
#include "game.h"
#include <stdlib.h>

bool is_swapping(char wrap){
    if (wrap=='S'){
        return true;
    }
    else if (wrap=='N'){
        return false;
    }
    
    else {
        fprintf(stderr,"ERROR NI S NI N\n");
        exit(EXIT_FAILURE);
    }
}
char swap(cgame g){
    if (g==NULL){
        exit(EXIT_FAILURE);
    }
    
    bool wrapp = game_is_wrapping(g);
    if(wrapp==true){
        return 'S';
    }
    else{
        return 'N';
    }    
}


game game_load(char *filename){ 
    if (filename==NULL){
        exit(EXIT_FAILURE);
    }
    FILE *f= fopen(filename,"r");
    if (f==NULL){
        fprintf(stderr,"error!\n");
        exit(EXIT_FAILURE);
    }
    
    uint w,h,nb_moves_max;
    char is_swap;
    fscanf(f,"%d %d %d %c\n",&w,&h,&nb_moves_max,&is_swap);

    color *colour = malloc(w* h * sizeof(color)); //il faut lire ligne par ligne les cases selon la hauteur et la largeur "<color[x][y]>"

    if(colour==NULL){
        free(colour);
        fclose(f);
        exit(EXIT_FAILURE);
    }
    uint k=0;
    for(uint i=0;i<h;i++){
        for(uint j=0;j<w;j++){
            fscanf(f,"%d",&colour[k]);

            k=k+1;
        }
        fprintf(f,"\n");
    }
    bool swapping = is_swapping(is_swap);
    
    fclose(f); 
    game g =  game_new_ext(w,h,colour,nb_moves_max,swapping);
    if (g==NULL){
        fprintf(stderr,"g is null\n");
        exit(EXIT_FAILURE);
    }
    free(colour);
    return g;
}


void game_save(cgame g, char *filename){ 
    if (g==NULL){
        exit(EXIT_FAILURE);
    }
    if (filename==NULL){
        exit(EXIT_FAILURE);
    }
    FILE *f = fopen(filename ,"w+");
    if (f==NULL){
        exit(EXIT_FAILURE);
    }
    fprintf(f,"%d %d %d %c\n",game_width(g),game_height(g),game_nb_moves_max(g),swap(g));
    for(uint i=0;i<game_height(g);i++){
        for(uint j=0;j<game_width(g);j++){
            if (j<(game_width(g)-1)){fprintf(f,"%d ",game_cell_current_color(g,i,j));}
            else{fprintf(f,"%d",game_cell_current_color(g,i,j));}
        }       
        
        fprintf(f,"\n");
    }
fclose(f);
}
#endif  
