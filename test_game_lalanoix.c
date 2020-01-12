#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_io.h"
#include "game.h"
#include "game.c"
#define WITDH 10
#define HEIGHT 10
/* ********** USAGE ********** */

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/* ********** TEST RESTART ********** */

bool test_game_restart(){
  color cell[]= {
      0,0,0,2,0,2,1,0,1,0,3,0,
      0,3,3,1,1,1,1,3,2,0,1,0,
      1,0,1,2,3,2,3,2,0,3,3,2,
      2,3,1,0,3,2,1,1,1,2,2,0,
      2,1,2,3,3,3,3,2,0,1,0,0,
      0,3,3,0,1,1,2,3,3,2,1,3,
      1,1,2,2,2,0,0,1,3,1,1,2,
      1,3,1,3,1,0,1,0,1,3,3,3,
      0,3,0,1,0,0,2,1,1,1,3,0,
      1,3,1,0,0,0,3,2,3,1,0,0,
      1,3,3,1,1,2,2,3,2,0,0,2,
      2,0,2,3,0,1,1,1,2,3,0,1
  };

  game g= game_new(cell,SIZE);
   if (g==NULL){
    fprintf(stderr, "ERROR! \n");
    return false;
  }

  if(game_nb_moves_cur(g)!=0){
    fprintf(stderr, "Error:nb moves cur\n");
    return false;
  }

  for (int x=0; x< SIZE;x++){
    for (int y=0; y<SIZE; y++){
      unsigned int cellc =game_cell_current_color(g,x,y);
      if(cellc<0 || cellc>3){
        fprintf(stderr, "Error: cell problem\n");

        return false;
      }
    }
  }

  game_delete(g);
  return true;
}
/* ********** TEST IS OVER ********** */

bool test_game_is_over(){
  

  color cell[]= {
      0,0,0,2,0,2,1,0,1,0,3,0,
      0,3,3,1,1,1,1,3,2,0,1,0,
      1,0,1,2,3,2,3,2,0,3,3,2,
      2,3,1,0,3,2,1,1,1,2,2,0,
      2,1,2,3,3,3,3,2,0,1,0,0,
      0,3,3,0,1,1,2,3,3,2,1,3,
      1,1,2,2,2,0,0,1,3,1,1,2,
      1,3,1,3,1,0,1,0,1,3,3,3,
      0,3,0,1,0,0,2,1,1,1,3,0,
      1,3,1,0,0,0,3,2,3,1,0,0,
      1,3,3,1,1,2,2,3,2,0,0,2,
      2,0,2,3,0,1,1,1,2,3,0,1
  };

  game g= game_new(cell,SIZE);

  if (g==NULL){
    fprintf(stderr, "ERROR! \n");
    return false;
  }


  if(game_nb_moves_cur(g)>game_nb_moves_max(g)){
    fprintf(stderr, "Error!\n");
    return false;
  }

  int sol[12] = {3,1,3,1,0,3,1,0,1,3,2,0};
  for (int i=0; i<12;i++){
    game_play_one_move(g, sol[i]);
  }

  if(!game_is_over(g)){
    fprintf(stderr, "Error 404!\n");
    return false;
    
  }
  game_delete(g);
  return true;
}

/* ********** TEST DELETE ********** */

bool test_game_delete(){

  game g= game_new_empty();
  if(g==NULL){
    fprintf(stderr, "ERROR! \n");
    return false;
  }

  game_delete(g);


  return true;
}

/* ********** TEST IS WRAPPING ********** */
bool test_iswrapping(){
  game g = game_new_empty_ext(WITDH,HEIGHT,true);
  if(game_is_wrapping(g)==false){
    fprintf(stderr, "Error!\n");
    game_delete(g);
    return false;
  }
  game_delete(g);
  return true;
}

/* ********** TEST WIDTH ********** */
bool test_width(){
    game g = game_new_empty();
    if (game_width(g) != g->width){
        fprintf(stderr, "Error: width!\n");
        return false;
    }
    return true;
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char *argv[]) {
  if (argc == 1) usage(argc, argv);

  // start test
  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  bool ok = false;
  if (strcmp("restart", argv[1]) == 0)
    ok = test_game_restart();
  else if (strcmp("delete", argv[1]) == 0)
    ok = test_game_delete();
  else if (strcmp("isover", argv[1]) == 0)
    ok = test_game_is_over();
  else if (strcmp("iswrapping", argv[1]) == 0)
    ok = test_iswrapping();
  else if (strcmp("width", argv[1]) == 0)
    ok = test_width();
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