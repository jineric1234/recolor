#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_io.h"


/* ********** TEST NB MOUVES ********** */
bool test_nbmovescur(){
  game g = game_new_empty();
  if (g == NULL){
    fprintf(stderr, "Error: invalid recolor init!\n");
    return false;
  }

  if (game_nb_moves_cur(g)> 0){
    fprintf(stderr, "Error: invalid recolor current moves!\n");
    game_delete(g);
    return false;
  }

  game_delete(g);
  return true;
}

/* ********** TEST ONE MOUVE ********** */

bool test_playonemouve(){
  game g = game_new_empty();
  if (g == NULL){
    fprintf(stderr, "Error: invalid recolor init!\n");
    return false;
  }

  unsigned int c=game_cell_current_color(g, 0, 0);
  if (c<0 && c>3){
    game_delete(g);
    return false;
  }

  game_delete(g);
  return true;
}

/* ********** TEST GAME COPY ********** */

bool test_copy(){
  game g = game_new_empty();
  if (g == NULL){
    fprintf(stderr, "Error: invalid recolor init!\n");
    return false;
  }

  game c = game_copy(g);
  if (c == NULL){
    fprintf(stderr, "Error: invalid copy of recolor init!\n");
    return false;
  }

  for (unsigned int x= 0; x<12; x++){
    for (unsigned int y= 0; y<12; y++){
      if (game_cell_current_color(g, x, y)!= game_cell_current_color(c, x, y)){
        fprintf(stderr, "Error: la copie n'est pas identique!\n");
        game_delete(g);
        game_delete(c);
        return false;
      }
    }
  }

  game_delete(g);
  game_delete(c);
  return true;

}


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
    ok = test_nbmovescur();
  else if (strcmp("playonemove", argv[1]) == 0)
    ok = test_playonemouve();
  else if (strcmp("copy", argv[1]) == 0){
    ok=test_copy();
  }
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