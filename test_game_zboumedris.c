#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.c"
#include "game.h"
#include "game_io.h"

bool test_game_set_max_moves(int k) {
  game g = game_new_empty();
  if (g == NULL) {
    fprintf(stderr, "Error: game not found!\n");
    return false;
  }
  game_set_max_moves(g, SIZE);
  for (unsigned int i = 0; i < SIZE; i++) {
    game_play_one_move(g, k);
    if (game_nb_moves_max(g) != SIZE) {
      fprintf(stderr, "Error: nombre max de jouer!\n");
      game_delete(g);
      return false;
    }
  }
  game_delete(g);
  return true;
}

bool test_game_nb_moves_max() {
  game g = game_new_empty();
  if (g == NULL) {
    fprintf(stderr, "Error: game not found!\n");
    return false;
  }

  if (game_nb_moves_max(g) > 12) {
    fprintf(stderr, "Error: condition d'arret de jeux! \n");
    game_delete(g);
    return false;
  }

  game_delete(g);
  return true;
}

bool test_game_cell_current_color() {
  game dgame = game_new_empty();
  color cell[] = {0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2,
                  0, 1, 0, 1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2,
                  1, 1, 1, 2, 2, 0, 2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3,
                  0, 1, 1, 2, 3, 3, 2, 1, 3, 1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
                  1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3, 0, 3, 0, 1, 0, 0, 2, 1, 1,
                  1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0, 1, 3, 3, 1, 1, 2,
                  2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  int i = 0;
  for (int x = 0; x < SIZE; x++) {
    for (int y = 0; y < SIZE; y++) {
      game_set_cell_init(dgame, x, y, *(cell + i));
      i = i + 1;
    }
  }
  return dgame;
  game g = game_new_empty();
  if (g == NULL) {
    fprintf(stderr, "Error: game not found!\n");
    return false;
  }

  for (uint y = 0; y < SIZE; y++) {
    for (uint x = 0; x < SIZE; x++) {
      unsigned int c = game_cell_current_color(g, x, y);
      if (c < 0 || c > 3) {
        fprintf(stderr, "Error: game not found!\n");
        game_delete(g);
        return false;
      }
    }
  }
  game_delete(g);
  return true;
}
 /*
bool test_game_height() {
  uint height = rand() % 15 + 9;
  game g = game_new_empty_ext(height, 9, true);
  if (g == NULL) {
    fprintf(stderr, "Error: game not found!\n");
    return false;
  }
  uint k = game_height(g);
  if (k != height) {
    return false;
  }
  return true;
} */

bool test_game_height(){
    game g = game_new_empty();
    if (game_height(g) != g->height){
        fprintf(stderr, "Error: height!\n");
        return false;
    }
    return true;
}

/* ********** USAGE ********** */

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char *argv[]) {
  if (argc == 1) usage(argc, argv);
  // start test

  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  bool ok = false;
  if (strcmp("setmax", argv[1]) == 0)
    ok = test_game_set_max_moves(2);
  else if (strcmp("nbmovesmax", argv[1]) == 0)
    ok = test_game_nb_moves_max();
  else if (strcmp("cellcolor", argv[1]) == 0)
    ok = test_game_cell_current_color();
  else if (strcmp("height", argv[1]) == 0)
    ok = test_game_height();
  else {
    fprintf(stderr,
            "Errorote: previous declaration of ‘game_delete’ was here: test "
            "\"%s\" not found!\n",
            argv[1]);
    exit(EXIT_FAILURE);
    void game_delete(game g);
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
