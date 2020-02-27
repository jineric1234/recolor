#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.c"
#include "game.h"
#include "game_io.h"

/* ****** TEST GAME DEFAULT ******** */

bool test_gamedef(){

  return true;
}

/* ******** TEST NB MOUVES ******** */
bool test_nbmovescur(int k, int c){ //error game02.o
  game g = game_new_empty();
  if (g == NULL){
    fprintf(stderr, "Error: invalid recolor init!\n");
    return false;
  }

  if (game_nb_moves_cur(g)!= 0){
    fprintf(stderr, "Error: invalid recolor current moves!\n");
    game_delete(g);
    return false;
  }

  for (int i=0; i<k; i++){game_play_one_move(g, c);}

  if (game_nb_moves_cur(g)!=k){
    fprintf(stderr, "Error: error in current moves!\n");
    game_delete(g);
    return false;
  }

  game_restart(g);
  if (game_nb_moves_cur(g)!=0){
    fprintf(stderr, "Error: error in restarting moves!\n");
    game_delete(g);
    return false;
  }

  game_delete(g);
  return true;
}

/* ******** TEST ONE MOUVE ******** */

bool test_playonemouve(int k, int b){
  game g = game_new_empty();
  if (g == NULL){
    fprintf(stderr, "Error: invalid recolor init!\n");
    return false;
  }

  uint c = game_cell_current_color(g, 0, 0);
  if (c>=NB_COLORS){
    fprintf(stderr, "Error: color< 0 or color > 3!\n");
    game_delete(g);
    return false;
  }
  uint move= game_nb_moves_cur(g);
  for (unsigned int i=0; i<b; i++){game_play_one_move(g, k);}

  uint c_cell=game_cell_current_color(g, 0, 0);

  if (k!=c_cell){
    fprintf(stderr, "Error: color didn't change!\n");
    game_delete(g);
    return false;
  }
  unsigned int move1= game_nb_moves_cur(g);

  if (move==move1){
    fprintf(stderr, "Error: mouvement didn't change!\n");
    game_delete(g);
    return false;
  }
  game_delete(g);
  return true;
}

/* ******** TEST GAME EXT ********* */
bool test_emptyext(int h, int w){
  game g = game_new_empty_ext(w,h,true);
  if (g == NULL
  || g-> cell == NULL
  || g-> cell_init == NULL){
    fprintf(stderr, "Error: invalid new empty ext!\n");
    return false;
  }
  if (g->nbmovecur!=0
  || g->nbmax!=0
  || g->height!=h
  || g->width!=w
  || g->wrapping!= true){
    fprintf(stderr, "1\n");
    return false;
  }
  for (uint i=0;  i<(g->width)*(g->height); i++){
    if (g->cell[i]!=0 || g->cell_init[i]!=0){
      fprintf(stderr, "2\n");
      return false;
    }
  }
  game_delete(g);
  return true;
}

/* ******** TEST GAME COPY ******** */

bool test_copy(int k, int width, int height, bool wrapping){
  game g = game_new_empty_ext(width, height, wrapping);
  if (g == NULL){
    fprintf(stderr, "Error: game g is NULL!\n");
    return false;
  }

  //test si la copy est identique a l'original
  game c = game_copy(g);
  if (c == NULL){
    fprintf(stderr, "Error: invalid copy of recolor init!\n");
    game_delete(g);
    return false;
  }
  if (g->height != c->height
  || g->width != c->width
  || g->wrapping != c->wrapping
  || g->nbmax != c->nbmax
  || g->nbmovecur != c->nbmovecur){
    fprintf(stderr, "Error: parameters not equal!\n");
    game_delete(c);
    game_delete(g);
    return false;
  }

  for (unsigned int x = 0; x<(g->height); x++){
    for (unsigned int y = 0; y<(g->height); y++){
      if (game_cell_current_color(g, x, y)!= game_cell_current_color(c, x, y)){
        fprintf(stderr, "Error: la copie n'est pas identique!\n");
        game_delete(g);
        game_delete(c);
        return false;
      }
    }
  }
  game_delete(c);

  //test copy apres des mouvements effectués
  for (uint i=0; i<5; i++){
    uint tab[]={2,1,0,3,2};
    game_play_one_move(g, tab[i]);
  }
  game v = game_copy(g);
  if (v==NULL){
    fprintf(stderr, "Error: la copie n.2 n'est pas identique!\n");
  }
  if (g->height != v->height
  || g->width != v->width
  || g->wrapping != v->wrapping
  || g->nbmax != v->nbmax
  || g->nbmovecur != v->nbmovecur){
    fprintf(stderr, "Error: parameters not equal!\n");
    game_delete(v);
    game_delete(g);
    return false;
  }

  for (unsigned int x= 0; x<(g->height); x++){
    for (unsigned int y= 0; y<(g->width); y++){
      if (game_cell_current_color(g, x, y)!= game_cell_current_color(v, x, y)){
        fprintf(stderr, "Error: la copie n.2 n'est pas identique!\n");
        game_delete(v);
        game_delete(g);
        return false;
      }
    }
  }
  game_delete(v);
  game_delete(g);
  return true;

}

/* ******** TEST GAME MAIN ******** */

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
  if (argc == 1) usage(argc, argv);

  // start test
  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  bool ok = false;
  if (strcmp("nbmovescur", argv[1]) == 0)
    ok = test_nbmovescur(20, 2);
  else if (strcmp("playonemove", argv[1]) == 0)
    ok = test_playonemouve(2, 30);
  else if (strcmp("copy", argv[1]) == 0)
    ok=test_copy(3, 7, 5, false);
  else if (strcmp("gamedef", argv[1]) == 0)
    ok=test_gamedef();
  else if ((strcmp("emptyext", argv[1]) == 0))
    ok=test_emptyext(5,7);
  else {
    fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  // print test result
  if (ok) {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}