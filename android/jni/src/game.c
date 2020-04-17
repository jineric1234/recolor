#include "game.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_io.h"

// Game structure
struct game_s {
  color* cell;       // tab with the colors of the current game
  color* cell_init;  // tab with the initial colors
  bool* tab_bool;    // tab with the changed zone
  uint nbmax;
  uint nbmovecur;
  uint width;
  uint height;
  bool wrapping;
};

// Game structure initialization
/**
 * @brief set perameters in game structure
 * @param g the game
 * @param cell game color tab
 * @param cell_tab game color tab to restart game
 * @param tab_bool game bool tab to the winned zone
 * @param nbmax maximal movement at game
 * @param nbmovecur current movement in game
 * @param width width
 * @param height height
 * @param wrapping boolean for is wrapping or not
 * @pre @p g is a valid pointer toward a game structure
 **/

void static test_coordinates(uint x, uint y, cgame g) {
  if (x >= game_width(g) || y >= game_height(g)) {
    game_delete((struct game_s*)g);
    fprintf(stderr, "Unvalid coordinates !\n");
    exit(EXIT_FAILURE);
  }
}

// Error detection

void static test_pointer(void* p) {
  if (!p) {
    fprintf(stderr, "Unvalid pointer !\n");
    exit(EXIT_FAILURE);
  }
}

void static test_game(cgame game) {
  if (game == NULL || !game->cell || !game->cell_init || !game->tab_bool) {
    game_delete((struct game_s*)game);
    fprintf(stderr, "unvalid game !\n");
    exit(EXIT_FAILURE);
  }
}

void game_color_neighbors(game g, color c_new, uint x, uint y) {
  test_game(g);
  test_coordinates(x, y, g);

  // upper cell : (x,y-1)
  // if the coordinates of the upper neighbor are valid and it is the same color
  if (y >= 1 && !g->tab_bool[(y - 1) * game_width(g) + x] && game_cell_current_color(g, x, y - 1) == c_new) {
    // color the cell and call function on its neighbors
    g->cell[(y - 1) * game_width(g) + x] = c_new;
    g->tab_bool[(y - 1) * game_width(g) + x] = true;
    game_color_neighbors(g, c_new, x, y - 1);
    // no need to worry about repeated neighbors because the old color is always
    // different from the new one
  }
  // lower cell : (x,y+1)
  if (y + 1 < game_height(g) && !g->tab_bool[(y + 1) * game_width(g) + x] && game_cell_current_color(g, x, y + 1) == c_new) {
    g->cell[(y + 1) * game_width(g) + x] = c_new;
    g->tab_bool[(y + 1) * game_width(g) + x] = true;
    game_color_neighbors(g, c_new, x, y + 1);
  }
  // left cell : (x-1,y)
  if (x >= 1 && !g->tab_bool[y * game_width(g) + (x - 1)] && game_cell_current_color(g, x - 1, y) == c_new) {
    g->cell[y * game_width(g) + (x - 1)] = c_new;
    g->tab_bool[y * game_width(g) + (x - 1)] = true;
    game_color_neighbors(g, c_new, x - 1, y);
  }
  // right cell : (x+1,y)
  if (x + 1 < game_width(g) && !g->tab_bool[y * game_width(g) + (x + 1)] && game_cell_current_color(g, x + 1, y) == c_new) {
    g->cell[y * game_width(g) + (x + 1)] = c_new;
    g->tab_bool[y * game_width(g) + (x + 1)] = true;
    game_color_neighbors(g, c_new, x + 1, y);
  }
  // if the game is wrapping, we check the other neighbors too
  if (game_is_wrapping(g)) {
    // (x,y) <=> y*game_width(g)+x
    // upper cell : (x,game_height(g)-1) <=> (game_height(g)-1)*game_width(g)+x
    if (y == 0 && !g->tab_bool[(game_height(g) - 1) * game_width(g) + x] && game_cell_current_color(g, x, game_height(g) - 1) == c_new) {
      // color the cell and call function on its neighbors
      g->cell[(game_height(g) - 1) * game_width(g) + x] = c_new;
      g->tab_bool[(game_height(g) - 1) * game_width(g) + x] = true;
      game_color_neighbors(g, c_new, x, game_height(g) - 1);
    }
    // lower cell : (x,0) <=> x
    if (y == game_height(g) - 1 && !g->tab_bool[x] && game_cell_current_color(g, x, 0) == c_new) {
      g->cell[x] = c_new;
      g->tab_bool[x] = true;
      game_color_neighbors(g, c_new, x, 0);
    }
    // left cell : (game_width(g)-1,y) <=> y*game_width(g)+game_width(g)-1
    if (x == 0 && !g->tab_bool[(y*game_width(g))+(game_width(g)-1)] && game_cell_current_color(g, game_width(g) - 1, y) == c_new) {
      g->cell[y * game_width(g) + game_width(g) - 1] = c_new;
      g->tab_bool[y * game_width(g) + game_width(g) - 1] = true;
      game_color_neighbors(g, c_new, game_width(g) - 1, y);
    }
    // right cell : (0,y) <=> y*game_width(g)
    if (x == game_width(g) - 1 && !g->tab_bool[y*game_width(g)] &&  game_cell_current_color(g, 0, y) == c_new) {
      g->cell[y * game_width(g)] = c_new;
      g->tab_bool[y * game_width(g)] = true;
      game_color_neighbors(g, c_new, 0, y);
    }
  }
  return;
}

void set_in_struct(game g, color* cell, color* cell_init, uint nbmax,
       int nbmovecur, uint width, uint height, bool wrapping, bool* t_bool) {

  g->cell = cell;
  g->cell_init = cell_init;
  g->nbmax = nbmax;
  g->nbmovecur = nbmovecur;
  g->width = width;
  g->height = height;
  g->wrapping = wrapping;
  g->tab_bool = t_bool;
}

game game_new_empty_ext(uint width, uint height, bool wrapping) {
  // we allocate the memory for the game, the 1st and 2nd tabs
  game new_empty_ext = (game)malloc(sizeof(struct game_s));
  if (!new_empty_ext) {
    fprintf(stderr, "Not enough memory for struct game_s !\n");
    exit(EXIT_FAILURE);
  }
  color* t = (color*)malloc(height * width * sizeof(color));
  if (!t) {
    free(new_empty_ext);
    fprintf(stderr, "Not enough memory for tab!\n");
    exit(EXIT_FAILURE);
  }
  color* t_init = (color*)malloc(height * width * sizeof(color));
  if (!t_init) {
    free(t);
    free(new_empty_ext);
    fprintf(stderr, "Not enough memory for init_tab!\n");
    exit(EXIT_FAILURE);
  }
  bool* tab_init = (bool*)malloc(height * width * sizeof(bool));
  if (!t_init) {
    free(t);
    free(t_init);
    free(new_empty_ext);
    fprintf(stderr, "Not enough memory for tab_init!\n");
    exit(EXIT_FAILURE);
  }

  // we fill both tabs with the color "0"
  for (uint i = 0; i < height * width; i++) {
    t[i] = 0;
    t_init[i] = 0;
    tab_init[i] = false;
  }
  tab_init[0] = true; //first is true
  set_in_struct(new_empty_ext, t, t_init, 0, 0, width, height, wrapping, tab_init);
  return new_empty_ext;
}

game game_new_ext(uint width, uint height, color* cells, uint nb_moves_max, bool wrapping) {
  test_pointer(cells);
  // we allocate the memory for the game
  game new_ext = (game)malloc(sizeof(struct game_s));
  if (!new_ext) {
    fprintf(stderr, "Not enough memory for struct game_s !\n");
    exit(EXIT_FAILURE);
  }
  // we allocate the memory for the first tab
  color* t = (color*)malloc(width * height * sizeof(color));
  if (!t) {
    free(new_ext);
    fprintf(stderr, "Not enough memory for tab!\n");
    exit(EXIT_FAILURE);
  }
  // we allocate the memory for the second tab
  color* t_init = (color*)malloc(width * height * sizeof(color));
  if (!t_init) {
    free(t);
    free(new_ext);
    fprintf(stderr, "Not enough memory for init_tab!\n");
    exit(EXIT_FAILURE);
  }
  //we allocate the memory for the boolean tab
  bool* tab_init = (bool*)malloc(height * width * sizeof(bool));
  if (!t_init) {
    free(t);
    free(t_init);
    free(new_ext);
    fprintf(stderr, "Not enough memory for tab_init!\n");
    exit(EXIT_FAILURE);
  }

  // we fill both tabs with the given colors
  for (uint i = 0; i < (width * height); i++) {
    t[i] = cells[i];
    t_init[i] = cells[i];
    tab_init[i] = false;
  }
  tab_init[0] = true;
  // we set the other parameters
  set_in_struct(new_ext, t, t_init, nb_moves_max, 0, width, height, wrapping, tab_init);
  int v = new_ext->cell[0];
  game_color_neighbors(new_ext,v,0,0);

  // we return the game
  return new_ext;
}

game game_new(color* cells, uint nb_moves_max) {
  return game_new_ext(SIZE, SIZE, cells, nb_moves_max, false);
}

game game_new_empty() {
  return game_new_empty_ext(SIZE, SIZE, false);
}

// Data recovery

uint game_height(cgame game) {
  test_game(game);
  uint h = game->height;
  return h;
}

uint game_width(cgame game) {
  test_game(game);
  return game->width;
}

bool game_is_wrapping(cgame game) {
  test_game(game);
  return game->wrapping;
}

uint game_nb_moves_max(cgame g) {
  test_game(g);
  uint n = g->nbmax;
  return n;
}

uint game_nb_moves_cur(cgame g) {
  test_game(g);
  int n = g->nbmovecur;
  return n;
}

color game_cell_current_color(cgame g, uint x, uint y) {
  test_game(g);
  test_coordinates(x, y, g);
  // (x,y) <=> y*game_width(g)+x
  return g->cell[y * game_width(g) + x];
}

// Set game parameters

void game_set_cell_init(game g, uint x, uint y, color c) {
  test_game(g);
  test_coordinates(x, y, g);
  // we set the case (x,y) to given color in both the initial and the current
  // game tabs
  g->cell_init[y * game_width(g) + x] = c;
  g->cell[y * game_width(g) + x] = c;
  return;
}

void game_set_max_moves(game g, uint nb_max_moves) {
  test_game(g);
  if (nb_max_moves < 1) {
    game_delete(g);
    fprintf(stderr, "Unvalid number of moves !\n");
    exit(EXIT_FAILURE);
  }
  g->nbmax = nb_max_moves;
  return;
}

// Apply game

/**
 * @brief Colors all the neighbours of the case (x,y) if they have
 * @param g the game
 * @param c the color
 * @param x the first coordinate of the cell
 * @param y the second coordinate of the cell
 * @pre @p g is a valid pointer toward a game structure
 * @pre 0 <= @p c_old < 16
 * @pre 0 <= @p c_new < 16
 * @pre @p c_old != @p c_new
 * @pre @p x < game_width(g)
 * @pre @p y < game_height(g)
 **/



void game_play_one_move(game g, color c) {
  test_game(g);
    // we color the first cell (0,0) and its neighbors
  for (uint i=1; i< (g->height * g->width); i++){
    if (g->tab_bool[i]==true){
      g->tab_bool[i]=false;
      g->cell[i]=c;
    }
    g->cell[0]=c;
  }
  game_color_neighbors(g, c, 0, 0);
  g->nbmovecur++;
  return;
}

// Tools

game game_copy(cgame g) {
  test_game(g);

  game copy =
      game_new_empty_ext(game_width(g), game_height(g), game_is_wrapping(g));
  // we copy both tabs and the other parameters
  for (uint i = 0; i < game_width(g) * game_height(g); i++) {
    copy->cell[i] = g->cell[i];
    copy->cell_init[i] = g->cell_init[i];
    copy->tab_bool[i] = g->tab_bool[i];
  }
  copy->nbmax = g->nbmax;
  copy->nbmovecur = g->nbmovecur;
  copy->width = g->width;
  copy->height = g->height;
  copy->wrapping = g->wrapping;

  return copy;
}

void game_delete(game g) {
  if (g) {
    if (g->cell) {
      free(g->cell);
    }
    if (g->cell_init) {
      free(g->cell_init);
    }
    if (g->tab_bool){
      free(g->tab_bool);
    }
    free(g);
  }
}

bool game_is_over(cgame g) {
  test_game(g);

  // if the current number of moves is different from the maximum, the game is
  // not over
  if (g->nbmovecur > g->nbmax) return false;

  // we compare all of the cells colors with the color of the cell (0,0)
  color c = g->cell[0];
  for (uint i = 1; i < game_width(g) * game_height(g); i++) {
    // if one of the cells is different from the first one, the game is not over
    if (g->cell[i] != c) return false;
  }
  

  // else the game is over
  return true;
}

void game_restart(game g) {
  test_game(g);
  // we set all the cells of the game to the initial colors
  for (uint i = 0; i < game_width(g) * game_height(g); i++) {
    g->cell[i] = g->cell_init[i];
    g->tab_bool[i] = false;
  }
  g->tab_bool[0] = true;
  // we reset the current number of moves
  game_play_one_move(g,(g->cell[0]));
  g->nbmovecur = 0;


}
