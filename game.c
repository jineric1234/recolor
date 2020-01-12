
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
  return g;
}

game game_new_empty() {
  game g = (game)malloc(sizeof(struct game_s));
  if (g == NULL) {
    fprintf(stderr, "errrr\n");
    exit(1);
  }
  g->nbmax = 0;
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
  if (c < 0 || c > 3 || x >= SIZE || y >= SIZE) {
    exit(EXIT_FAILURE);
  }
  g->cell_init[(x * SIZE) + y] = c;
  g->cell[(x * SIZE) + y] = c;
}

void game_set_max_moves(game g, uint nb_max_moves) {
  if (g == NULL || nb_max_moves == 0) {
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
  if (g == NULL || x >= SIZE || y >= SIZE) {
    fprintf(stderr, "mauvais données pour game_cell_current_color \n");
    exit(EXIT_FAILURE);
  }
  return g->cell[(x * SIZE) + y];
}

game game_copy(cgame g) {
  if (g == NULL) {
    fprintf(stderr, "POINTEUR null\n");
    exit(EXIT_FAILURE);
  }
  game game_copy = game_new_empty();
  for (int i = 0; i < SIZE * SIZE; i++) {
    game_copy->cell[i] = g->cell[i];
    game_copy->cell_init[i] = g->cell_init[i];
    game_copy->tab[i] = g->tab[i];
    game_copy->tab_init[i] = g->tab_init[i];
  }
  game_copy->nbmax = g->nbmax;
  game_copy->nbmovecur = g->nbmovecur;
  return game_copy;
}

uint game_nb_moves_cur(cgame g) {
  if (g == NULL) {
    fprintf(stderr, "pointeur games_nb_moves_cur null\n");
    exit(EXIT_FAILURE);
  }
  return g->nbmovecur;
}

bool estValide(int x, int y){
    if (x<0 || x>=SIZE || y<0 || y>=SIZE){
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
  int height = g->height;
  int width = g->width;
  color c = game_cell_current_color(g, 0, 0);
  for (uint i=0; i<SIZE*SIZE; i++){
    int x = i/SIZE;
    int y = i%SIZE;
    if (g->tab[i]==true){
      if (g->wrapping==false){ //wrapping false jeu normal
        if (estValide(x ,y+1)){
            if (game_cell_current_color(g, x, y+1)==c){
                g->tab[x*SIZE+y+1]=true;
            }
        }
        if (estValide(x,y-1)){
            if (game_cell_current_color(g, x, y-1)==c){
                g->tab[x*SIZE+y-1]=true;
            }
        }
        if (estValide(x-1,y)){
            if (game_cell_current_color(g, x-1, y)==c){
                g->tab[(x-1)*SIZE+y]=true;
            }
        }
        if (estValide(x+1 ,y)){
            if (game_cell_current_color(g, x+1, y)==c){
                g->tab[(x+1)*SIZE+y]=true;
            }
        }
        g->cell[i]=v;
      }
      else{ //wrapping true chang regles
        if (y<(width-1)){ //case de droite
          if (game_cell_current_color(g, x, 0)==c){
            g->tab[x*height]=true;
          }
        }
        else{
          if (game_cell_current_color(g, x, y)==c){
            g->tab[x*height+y+1]=true;
          }
        }
        if (y==0){ //case de gauche
          if (game_cell_current_color(g, x, (width-1))==c){
              g->tab[x*height+(width-1)]=true;
          }
        }
        else{
          if (game_cell_current_color(g, x, y-1)==c){
              g->tab[x*height+y-1]=true;
          }
        }
        if (x==0){ //case haut
          if (game_cell_current_color(g, (height-1), y)==c){
            g->tab[(height-1)*(height-1)+y]=true;
          }
        }
        else{
          if (game_cell_current_color(g, x-1, y)==c){
            g->tab[(x-1)*height+y]=true;
          }
        }
        if (x==(height-1)){ // case en bas
          if (game_cell_current_color(g, 0, y)==c){
              g->tab[y]=true;
          }
        }
        else{
          if (game_cell_current_color(g, x+1, y)==c){
              g->tab[(x+1)*height+y]=true;
          }
        }
        g->cell[i]=v;
      }
    }
  }
  for (uint i=(SIZE*SIZE)-1; i>0; i--){
    uint x = i/SIZE;
    uint y = i%SIZE;
    if (g->tab[i]==true){
      if (g->wrapping==false){ //wrapping false jeu normal
        if (estValide(x ,y+1)){
            if (game_cell_current_color(g, x, y+1)==c){
                g->tab[x*SIZE+y+1]=true;
            }
        }
        if (estValide(x,y-1)){
            if (game_cell_current_color(g, x, y-1)==c){
                g->tab[x*SIZE+y-1]=true;
            }
        }
        if (estValide(x-1,y)){
            if (game_cell_current_color(g, x-1, y)==c){
                g->tab[(x-1)*SIZE+y]=true;
            }
        }
        if (estValide(x+1 ,y)){
            if (game_cell_current_color(g, x+1, y)==c){
                g->tab[(x+1)*SIZE+y]=true;
            }
        }
        g->cell[i]=v;
      }
      else{ //wrapping true chang regles
        if (y<(width-1)){ //case de droite
          if (game_cell_current_color(g, x, 0)==c){
            g->tab[x*height]=true;
          }
        }
        else{
          if (game_cell_current_color(g, x, y)==c){
            g->tab[x*height+y+1]=true;
          }
        }
        if (y==0){ //case de gauche
          if (game_cell_current_color(g, x, (width-1))==c){
              g->tab[x*height+(width-1)]=true;
          }
        }
        else{
          if (game_cell_current_color(g, x, y-1)==c){
              g->tab[x*height+y-1]=true;
          }
        }
        if (x==0){ //case haut
          if (game_cell_current_color(g, (height-1), y)==c){
            g->tab[(height-1)*(height-1)+y]=true;
          }
        }
        else{
          if (game_cell_current_color(g, x-1, y)==c){
            g->tab[(x-1)*height+y]=true;
          }
        }
        if (x==(height-1)){ // case en bas
          if (game_cell_current_color(g, 0, y)==c){
              g->tab[y]=true;
          }
        }
        else{
          if (game_cell_current_color(g, x+1, y)==c){
              g->tab[(x+1)*height+y]=true;
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
  for (int i = 1; i < SIZE * SIZE; i++) {
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
  if (g->cell_init == NULL || g->tab_init == NULL || g->cell == NULL ||
      g->tab == NULL) {
    fprintf(stderr, "erruer structure   \n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < SIZE * SIZE; i++) {
    g->cell[i] = g->cell_init[i];
    g->tab[i] = g->tab_init[i];
  }
}

/*******************************V2********************************/

bool game_is_wrapping(cgame g) { 
  if (g==NULL){
    fprintf(stderr,"error pointer!\n");
  }
  return g->wrapping;
}

game game_new_empty_ext(uint width, uint height, bool wrapping){
  game g = (game)malloc(sizeof(struct game_s));
  if (g == NULL) {
    fprintf(stderr, "errrr\n");
    exit(EXIT_FAILURE);
  }
  g->nbmax = 0;
  g->nbmovecur = 0;
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
  for (int i = 0; i < width * height; i++) {
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
  g->wrapping=wrapping;
  return g;
}

 

game game_new_ext(uint width, uint height, color *cells, uint nb_moves_max, bool wrapping) {
  if (nb_moves_max == 0) {
    fprintf(stderr, "moves max egale a zero");
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
  game g = (game)malloc(sizeof(struct game_s));
  if (g == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    exit(EXIT_FAILURE);
  }
  g->nbmax = nb_moves_max;
  g->nbmovecur = 0;
  g->width = width;
  g->height = height;
  g->cell = (color *)malloc(g->width * g->width * sizeof(color)); /* j'ai changé SIZE*SIZE par wdith*height*/
  if (g->cell == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g);
    exit(EXIT_FAILURE);
  }
  g->cell_init = (color *)malloc(g->width * g->height * sizeof(color));
  if (g->cell_init == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g->cell);
    free(g);
    exit(EXIT_FAILURE);
  }
  g->tab = (bool *)malloc(g->width * g->height * sizeof(bool));
  if (g->tab == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g->cell_init);
    free(g->cell);
    free(g);
    exit(EXIT_FAILURE);
  }
  g->tab_init = (bool *)malloc(g->width * g->height * sizeof(bool));
  if (g == NULL) {
    fprintf(stderr, "jeu non initialisé\n");
    free(g->cell_init);
    free(g->cell);
    free(g->tab);
    free(g);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < g->width * g->height; i++) {
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
  g->wrapping=wrapping;
  
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
