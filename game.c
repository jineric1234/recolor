
#include "game.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_io.h"


struct game_s {
  color *cell;       // pointe vers la grille du jeu
  color *cell_init;  // pointe vers la grille du jeu initiale
  uint nbmax;        // nombre max de move
  uint nbmovecur;    // nombre de mouvements actuel
  bool *tab;         // deuxieme tableau pour les cases voisines
  bool *tab_init;    // copie tableau booleens
  bool wrapping;
  unsigned int width;
  unsigned int height;
};




game game_new(color *cells, uint nb_moves_max) {
  if (nb_moves_max == 0) {
    fprintf(stderr, "moves max egale a zero");
    exit(EXIT_FAILURE);
  }
  if (cells == NULL) {
    fprintf(stderr, "cells egale a null\n");
    exit(EXIT_FAILURE);
  }
  game g = (game)malloc(sizeof(struct game_s));
  if (g == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    exit(EXIT_FAILURE);
  }
  g->nbmax = nb_moves_max;
  g->nbmovecur = 0;
  g->cell = (color *)malloc(SIZE * SIZE * sizeof(color));
  if (g->cell == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g);
    exit(EXIT_FAILURE);
  }
  g->cell_init = (color *)malloc(SIZE * SIZE * sizeof(color));
  if (g->cell_init == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g->cell);
    free(g);
    exit(EXIT_FAILURE);
  }
  g->tab = (bool *)malloc(SIZE * SIZE * sizeof(bool));
  if (g->tab == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g->cell_init);
    free(g->cell);
    free(g);
    exit(EXIT_FAILURE);
  }
  g->tab_init = (bool *)malloc(SIZE * SIZE * sizeof(bool));
  if (g == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g->cell_init);
    free(g->cell);
    free(g->tab);
    free(g);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < SIZE * SIZE; i++) {
    g->cell[i] = cells[i];
    g->cell_init[i] = cells[i];
    if (i == 0) {
      g->tab[i] = true;
      g->tab_init[i] = true;
    } else {
      g->tab[i] = false;
      g->tab_init[i] = false;
    }
  }
  g->wrapping=false;
  g->height=SIZE;
  g->width=SIZE;
  return g;
}

game game_new_empty() {
  game g = (game)malloc(sizeof(struct game_s));
  if (g == NULL) {
    fprintf(stderr, "errrr\n");
    exit(1);
  }

  g->nbmax = 0;
  g->width=SIZE;
  g->height=SIZE;
  g->nbmovecur = 0;
  g->cell = (color *)malloc(SIZE * SIZE * sizeof(color));
  if (g->cell == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g);
    exit(EXIT_FAILURE);
  }
  g->cell_init = (color *)malloc(SIZE * SIZE * sizeof(color));
  if (g->cell_init == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g->cell);
    free(g);
    exit(EXIT_FAILURE);
  }
  g->tab = (bool *)malloc(SIZE * SIZE * sizeof(bool));
  if (g->tab == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g->cell_init);
    free(g->cell);
    free(g);
    exit(EXIT_FAILURE);
  }
  g->tab_init = (bool *)malloc(SIZE * SIZE * sizeof(bool));
  if (g == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g->cell_init);
    free(g->cell);
    free(g->tab);
    free(g);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < SIZE * SIZE; i++) {
    g->cell_init[i] = 0;
    g->cell[i] = 0;
    if (i == 0) {
      g->tab[i] = true;
      g->tab_init[i] = true;
    } else {
      g->tab[i] = false;
      g->tab_init[i] = false;
    }
  }
  return g;
}

void game_set_cell_init(game g, uint x, uint y, color c) {
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  if (c < 0 || c >=NB_COLORS || x >= g->height || y >= g->width) {
    exit(EXIT_FAILURE);
  }
  g->cell_init[(x * (g->height)) + y] = c;
  g->cell[(x * (g->height)) + y] = c;
}

void game_set_max_moves(game g, uint nb_max_moves) {
  if (g == NULL || nb_max_moves <= 0) {
    fprintf(stderr, "not enogh memory!\n");
    exit(EXIT_FAILURE);
  }
  g->nbmax = nb_max_moves;
}

uint game_nb_moves_max(cgame g) {
  if (g == NULL) {
    fprintf(stderr, "not enogh memory!\n");
    exit(EXIT_FAILURE);
  }
  return g->nbmax;
}

color game_cell_current_color(cgame g, uint x, uint y) {
  if (g == NULL) {
    fprintf(stderr, "mauvais données pour game_cell_current_color \n");
    exit(EXIT_FAILURE);
  }
  if ( x >= (g->width) || y >= (g->height)) {
    fprintf(stderr, "mauvais données pour  height game_cell_current_color \n");
    exit(EXIT_FAILURE);
  }
  return g->cell[(x * (g->height)) + y];
}

game game_copy(cgame g) {
  if (g == NULL) {
    fprintf(stderr, "POINTEUR null\n");
    exit(EXIT_FAILURE);
  }
  game game_copy = game_new_empty_ext(g->width, g->height, g->wrapping);
  if (game_copy==NULL){
    fprintf(stderr, "error creatin struct of copy\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < ((g->height) * (g->width)); i++) {
    game_copy->cell[i] = g->cell[i];
    game_copy->cell_init[i] = g->cell_init[i];
    game_copy->tab[i] = g->tab[i];
    game_copy->tab_init[i] = g->tab_init[i];
  }
  game_copy->nbmax = g->nbmax;
  game_copy->nbmovecur = g->nbmovecur;
  game_copy->height = g->height;
  game_copy->width = g->width;
 
  return game_copy;
}

uint game_nb_moves_cur(cgame g) {
  if (g == NULL) {
    fprintf(stderr, "pointeur games_nb_moves_cur null\n");
    exit(EXIT_FAILURE);
  }
  return g->nbmovecur;
}

bool estValide(game g, int x, int y){
    if (x<0 || x>=(g->height) || y<0 || y>=(g->width)){
      return false;
    }else{
      return true;
    }
}

void game_play_one_move(game g, color v){
  if (g==NULL){
      fprintf(stderr, "POINTEUR null\n");
      exit(EXIT_FAILURE);
  }
  if (v<0 || v>=NB_COLORS){
      fprintf(stderr, "Couleur innexistante\n");
      exit(EXIT_FAILURE);
  }
  g->nbmovecur++;
  int height = g->height; //evite de reecrire g->height
  int width = g->width; //evite de reecrire g->width
  color c = game_cell_current_color(g, 0, 0);
  for (uint i=0; i<(height*width); i++){
    int x = i/height;
    int y = i%height;
    if (g->tab[i]==true){
      if (g->wrapping==false){ //wrapping false jeu normal
        if (estValide(g, x ,y+1)){//case droite
            if (game_cell_current_color(g, x, y+1)==c){
                g->tab[x*height+y+1]=true;
            }
        }
        if (estValide(g, x,y-1)){//case gauche
            if (game_cell_current_color(g, x, y-1)==c){
                g->tab[x*height+y-1]=true;
            }
        }
        if (estValide(g, x-1,y)){//case superieure
            if (game_cell_current_color(g, x-1, y)==c){
                g->tab[(x-1)*height+y]=true;
            }
        }
        if (estValide(g, x+1 ,y)){//case inferieure
            if (game_cell_current_color(g, x+1, y)==c){
                g->tab[(x+1)*height+y]=true;
            }
        }
        g->cell[i]=v;
      }
      else{ //wrapping true changement regles
        if (y==(height-1)){ //case de droite
          if (game_cell_current_color(g, x, 0)==c){
            g->tab[x*height]=true;
          }
        }
        if (y<(height-1)){
          if (game_cell_current_color(g, x, y+1)==c){
            g->tab[x*height+y+1]=true;
          }
        }
        if (y==0){ //case de gauche
          if (game_cell_current_color(g, x, (width-1))==c){
              g->tab[x*height+(height-1)]=true;
          }
        }
        if (y!=0){
          if (game_cell_current_color(g, x, y-1)==c){
              g->tab[x*height+y-1]=true;
          }
        }
        if (x==0){ //case haut
          if (game_cell_current_color(g, (width-1), y)==c){
            g->tab[((width-1)*height)+y]=true;
          }
        }
        if (x!=0){
          if (game_cell_current_color(g, x-1, y)==c){
            g->tab[(x-1)*height+y]=true;
          }
        }
        if (x==(width-1)){ // case en bas
          if (game_cell_current_color(g, 0, y)==c){
              g->tab[y]=true;
          }
        }
        if (x!=(width-1)){
          if (game_cell_current_color(g, x+1, y)==c){
              g->tab[(x+1)*width+y]=true;
          }
        }
        g->cell[i]=v;
      }
    }
  }
  for (uint i=(height*width); i>0; i--){
    int x = i/height;
    int y = i%height;
    if (g->tab[i]==true){
      if (g->wrapping==false){ //wrapping false jeu normal
        if (estValide(g, x ,y+1)){//case droite
            if (game_cell_current_color(g, x, y+1)==c){
                g->tab[x*height+y+1]=true;
            }
        }
        if (estValide(g, x,y-1)){//case gauche
            if (game_cell_current_color(g, x, y-1)==c){
                g->tab[x*height+y-1]=true;
            }
        }
        if (estValide(g, x-1,y)){//case superieure
            if (game_cell_current_color(g, x-1, y)==c){
                g->tab[(x-1)*height+y]=true;
            }
        }
        if (estValide(g, x+1 ,y)){//case inferieure
            if (game_cell_current_color(g, x+1, y)==c){
                g->tab[(x+1)*height+y]=true;
            }
        }
        g->cell[i]=v;
      }
      else{ //wrapping true changement regles
        if (y==(height-1)){ //case de droite
          if (game_cell_current_color(g, x, 0)==c){
            g->tab[x*height]=true;
          }
        }
        if (y<(height-1)){
          if (game_cell_current_color(g, x, y+1)==c){
            g->tab[x*height+y+1]=true;
          }
        }
        if (y==0){ //case de gauche
          if (game_cell_current_color(g, x, (height-1))==c){
              g->tab[x*height+(height-1)]=true;
          }
        }
        if (y!=0){
          if (game_cell_current_color(g, x, y-1)==c){
              g->tab[x*height+y-1]=true;
          }
        }
        if (x==0){ //case haut
          if (game_cell_current_color(g, (width-1), y)==c){
            g->tab[((width-1)*height)+y]=true;
          }
        }
        if (x!=0){
          if (game_cell_current_color(g, x-1, y)==c){
            g->tab[(x-1)*height+y]=true;
          }
        }
        if (x==(width-1)){ // case en bas
          if (game_cell_current_color(g, 0, y)==c){
              g->tab[y]=true;
          }
        }
        if (x!=(width-1)){
          if (game_cell_current_color(g, x+1, y)==c){
              g->tab[(x+1)*width+y]=true;
          }
        }
        g->cell[i]=v;
      }
    }
  }
}

void game_delete(game g) {
  if (g == NULL) {
    fprintf(stderr, "pointeur null\n");
    exit(EXIT_SUCCESS);
  }
  free(g->cell);
  free(g->cell_init);
  free(g->tab);
  free(g->tab_init);
  free(g);
}

bool game_is_over(cgame g) {
  if (g == NULL) {
    fprintf(stderr, "pointeur game is over est null\n");
    exit(EXIT_FAILURE);
  }
  if (g->nbmovecur > g->nbmax) {
    return false;
  }
  uint x = g->cell[0];
  for (int i = 1; i < (g->height) * (g->width); i++) {
    if (g->cell[i] != x) {
      return false;
    }
  }
  return true;
}

void game_restart(game g) {
  if (g == NULL) {
    fprintf(stderr, "pointeur null\n");
    exit(EXIT_FAILURE);
  }
  g->nbmovecur = 0;
  if (g->cell_init == NULL 
  || g->tab_init == NULL
  || g->cell == NULL 
  || g->tab == NULL) {
    fprintf(stderr, "erruer structure \n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < (g->height * g->width); i++) {
    g->cell[i] = g->cell_init[i];
    g->tab[i] = g->tab_init[i];
  }
}

/*******************************V2********************************/

bool game_is_wrapping(cgame g) { 
  if (g==NULL){
    fprintf(stderr,"error pointer!\n");
  }
  if (g->wrapping != true && g->wrapping != false){
    fprintf(stderr,"error wprapping!\n");
  }
  return g->wrapping;
}

game game_new_empty_ext(uint width, uint height, bool wrapping){
  game g = (game)malloc(sizeof(struct game_s));
  if (g == NULL) {
    fprintf(stderr, "errrr\n");
    exit(EXIT_FAILURE);
  }

  if (width <= 0
  || height <= 0
  || (wrapping != true && wrapping != false)){
    fprintf(stderr, "Error in parametre! \n");
    exit(EXIT_FAILURE);
  }

  g->nbmovecur = 0;
  g->height=height;
  g->width=width;
  g->wrapping=wrapping;

  g->cell = (color *)malloc(width * height * sizeof(color));
  if (g->cell == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g);
    exit(EXIT_FAILURE);
  }
  g->cell_init = (color *)malloc(width * height * sizeof(color));
  if (g->cell_init == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g->cell);
    free(g);
    exit(EXIT_FAILURE);
  }
  g->tab = (bool *)malloc(width * height * sizeof(bool));
  if (g->tab == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g->cell_init);
    free(g->cell);
    free(g);
    exit(EXIT_FAILURE);
  }
  g->tab_init = (bool *)malloc(width * height * sizeof(bool));
  if (g == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g->cell_init);
    free(g->cell);
    free(g->tab);
    free(g);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < (width * height); i++) {
    g->cell_init[i] = 0;
    g->cell[i] = 0;
    if (i == 0) {
      g->tab[i] = true;
      g->tab_init[i] = true;
    } else {
      g->tab[i] = false;
      g->tab_init[i] = false;
    }
  }
  return g;
} 

game game_new_ext(uint width, uint height, color *cells, uint nb_moves_max, bool wrapping) {
  if (nb_moves_max == 0) {
    fprintf(stderr, "moves max egale a zero\n");
    exit(EXIT_FAILURE);
  }
  if (cells == NULL) {
    fprintf(stderr, "cells egale a null\n");
    exit(EXIT_FAILURE);
  }
  if(width<=0 || height<=0){
    fprintf(stderr, "width ou height inferieur ou égale a 0\n");
    exit(EXIT_FAILURE);
  }
  if (wrapping != true && wrapping != false){
    fprintf(stderr, "Error wrapping\n");
    exit(EXIT_FAILURE);
  }
    //repmlisage de la structure 
  game g =  malloc(sizeof(struct game_s));
  if (g == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    exit(EXIT_FAILURE);
  }

  g->wrapping = wrapping;
  g->nbmax = nb_moves_max;
  g->nbmovecur = 0;
  g->width = width;
  g->height = height;

  g->cell = (color *) malloc(width * height * sizeof(color)); /* j'ai changé SIZE*SIZE par wdith*height*/
  if (g->cell == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g);
    exit(EXIT_FAILURE);
  }
  g->cell_init = (color *) malloc(width * height * sizeof(color));
  if (g->cell_init == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g->cell);
    free(g);
    exit(EXIT_FAILURE);
  }
  g->tab = (bool *)malloc(width * height * sizeof(bool));
  if (g->tab == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g->cell_init);
    free(g->cell);
    free(g);
    exit(EXIT_FAILURE);
  }
  g->tab_init =  (bool *)malloc(width * height * sizeof(bool));
  if (g == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g->cell_init);
    free(g->cell);
    free(g->tab);
    free(g);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < (width * height); i++) {
    g->cell[i] = cells[i];
    g->cell_init[i] = cells[i];
    if (i == 0) {
      g->tab[i] = true;
      g->tab_init[i] = true;
    } else {
      g->tab[i] = false;
      g->tab_init[i] = false;
    }
  }
  
  return g;
}

uint game_height(cgame game) {
  if (game == NULL) {
    fprintf(stderr, "NULL pointer");
    exit(EXIT_FAILURE);
  }
  return game->height;
}

uint game_width(cgame game) {
    if (game == NULL) {
    fprintf(stderr, "NULL pointer");
    exit(EXIT_FAILURE);
  }
  return game->width;
}