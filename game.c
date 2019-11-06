#define SIZE 12
color cell[144];

typedef enum color_e {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    NB_COLORS
} color;

typedef struct game_s {
    color *cell; //pointe vers la grille du jeu
    uint nbmax; /* nombre max de move */
}game;


typedef unsigned int uint;

typedef const struct game_s *cgame;

