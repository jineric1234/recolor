#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.c"
#include "game.h"
#include "game_io.h"
#define nbmaxd 12


/* ******** TEST_GAME_NEW ********* */
bool test_game_new(){
  color cell[] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0,
      0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2,
      2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0,
      0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
      1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0,
      1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2,
      2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  
  game g = game_new(cell, SIZE);
  if (g == NULL){
    fprintf(stderr, "Error: invalid game new !\n");
    return false;
  }

  if (g->nbmax != SIZE
  ||g->nbmovecur != 0){
    fprintf(stderr, "Error: invalid nb_moves_max !\n ");
    game_delete(g);
    return false;
  }

  if (g->height != SIZE
  || g->height <=0
  || g->width <=0
  || g->width != SIZE){
    fprintf(stderr, "Error: invalid nb moves cur !\n");
    game_delete(g);
    return false;
  }
  
  for (uint i=0; i<(g->height*g->width)-1; i++){
    uint v = g->cell[i];
    uint w = g->cell[i+1];
    if (v != w){
      fprintf(stderr, "Error case not equal");
      game_delete(g);
      return false;
    }
  }

  for (unsigned int x = 0; x < (g->height); x++){
    for (unsigned int y = 0; y < (g->width); y++){
      if (game_cell_current_color(g, x, y) < 0 || game_cell_current_color(g, x, y) >= NB_COLORS){
        fprintf(stderr, "Error: cell color!\n");
        game_delete(g);
        return false;
      }
      if (g->cell[x] != g->cell_init[x]){
        fprintf(stderr, "Error: tab/ cell !\n");
        game_delete(g);
        return false;
      }
    }
  }
  game_delete(g);

  return true;
}

/* ********* TEST_NEW_EMPTY ********* */
bool test_game_new_empty(){
  game g = game_new_empty();
  if (g == NULL){
    fprintf(stderr, "Error: invalid recolor init!\n");
    return false;
  }

  if (g->nbmovecur != 0
  || g->nbmax != SIZE
  || g->wrapping != false){
    fprintf(stderr, "Error: move cur/ moves max/ wrapping ");
    game_delete(g);
    return false;
  }
  
  for (unsigned int x = 0; x < SIZE; x++){
    for (unsigned int y = 0; y < SIZE; y++){
      if (game_cell_current_color(g, x, y) != 0){
        fprintf(stderr, "Error: cells not have the default color (RED)!\n");
        game_delete(g);
        return false;
      }
    }
  }

  for (uint i=0; i<(SIZE*SIZE)-1; i++){
    uint v = sizeof(g->cell[i]);
    uint w = sizeof(g->cell[i+1]);
    if (v != w ){
      fprintf(stderr, "Error size not equal");
      game_delete(g);
      return false;
    }
  }

  game_delete(g);
  return true;
}

/* ********* TEST_GAME_SET_CELL_INIT ********* */
bool test_game_set_cell_init(){
  color cell[] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0,
      0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2,
      2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0,
      0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
      1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0,
      1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2,
      2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  game g = game_new_empty();
  if (g == NULL){
    fprintf(stderr, "Error: invalid game g!\n");
    return false;
  }

  for (uint x=0; x<SIZE; x++){
    for (uint y=0; y<SIZE; y++){
      game_set_cell_init(g, x, y, cell[x*SIZE+y]);
      if (game_cell_current_color(g,x,y) != cell[x*SIZE+y]){
        fprintf(stderr, "Error: invalid cell color!\n");
        game_delete(g);
        return false;
      }
    }
  }
  game_delete(g);
  return true;
}

/* **********************TEST_NEW_GAME_EXT****************/
bool test_newext(uint height, uint width){
  color cell[] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0,
      0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2,
      2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0,
      0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
      1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0,
      1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2,
      2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  
  game g = game_new_ext(width, height, cell, nbmaxd, true);
  if (g == NULL){
    fprintf(stderr, "error: invalid game new !\n");
    return false;
  }
  
  if(g->wrapping!=true){
    fprintf(stderr,"wrapping problem");
    game_delete(g);
    return false;
  }

  if(g->width != width 
  || g->height != height){
    fprintf(stderr, "width ou height problem");
    game_delete(g);
    return false;
  }

  if (g->nbmax != nbmaxd
  || g->nbmovecur != 0){
    fprintf(stderr, "error: invalid nbmax/ nbmovecur !\n ");
    game_delete(g);
    return false;
  }

  for (uint x = 0; x < height; x++){
    for (uint y = 0; y < width; y++){
      if (game_cell_current_color(g, x, y) < 0
      || game_cell_current_color(g, x, y) >= NB_COLORS
      || g->cell[x*width+y] != g->cell_init[x*width+y]){
        fprintf(stderr, "Error: parametrs struct!\n");
        game_delete(g);
        return false;
      }
    }
  }

  for (uint i=0; i<(height*width)-1; i++){
    uint v = sizeof(g->cell[i]);
    uint w = sizeof(g->cell[i+1]);
    if (v != w){
      fprintf(stderr, "Error size not equal");
      game_delete(g);
      return false;
    }
  }

  game_delete(g);
  return true;
}

/* ********** USAGE ********** */

void usage(int argc, char *argv[])
{
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char *argv[]){
  if (argc == 1)
    usage(argc, argv);

  // start test
  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  bool ok = false;
  if (strcmp("new", argv[1]) == 0)
    ok = test_game_new();
  else if (strcmp("newempty", argv[1]) == 0)
    ok = test_game_new_empty();
  else if (strcmp("setcell", argv[1]) == 0)
    ok = test_game_set_cell_init();
  else if (strcmp("newext", argv[1]) == 0)
    ok = test_newext(SIZE,SIZE);
  else
  {
    fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  // print test result
  if (ok)
  {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  }
  else
  {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}