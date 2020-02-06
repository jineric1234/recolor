/* Laura ALANOIX */
/* Ayoub NOUAMANI*/
// Zineb Boumedris

#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "game_io.h"

game game_default(){
    color cell[] = 
    { 0,0,0,2,0,2,1,0,1,0,3,0,
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
      2,0,2,3,0,1,1,1,2,3,0,1,
    };
  game dgame = game_new_ext(SIZE, SIZE, cell, 12, false);
  return dgame;
}

void game_display(game g){
    int nb_joues = game_nb_moves_cur(g);
    int nb_max = game_nb_moves_max(g);
    uint height = game_height(g);
    uint width = game_width(g);

    printf("nb de coups joués : %d ; nb de coups max : %d \n", nb_joues, nb_max);
    for (int x= 0; x < height; x++){
        for(int y= 0; y < width; y++){
            int v = game_cell_current_color(g, x, y);
            if (v>=0 && v<=9){printf("%d",v);}
            if (v==49){printf("a");}
            if (v==50){printf("b");}
            if (v==51){printf("c");}
            if (v==52){printf("d");}
            if (v==53){printf("e");}
            if (v==54){printf("f");}
        }
        printf("\n");
    }
    if(nb_joues==0){
    printf("Jouer un coup: (0,1,2,3,r ou q ;  r pour redémarrer ou q pour quitter)\n");
    } else {
         printf("Jouer un coup: (num couleur ou r pour redemarrer ou q pour quitter)\n");
    }
}
/*
int main(void){
    game g = game_default();
    game_set_max_moves(g, SIZE);
    game_display(g);

    while (game_is_over(g)==false){
        char value= getchar();
        if (value >= 48 && value <= 51){ valeur de 1, 2, 3 et 0
            value=value-48;
            game_play_one_move(g, value);
            game_display(g);
        }
         Restart le jeu 
        if (value == 82 || value == 114){ valeur de r et R
            game_restart(g);
            game_display(g);
        }
        
        Quitter le jeu 
        if (value == 81 || value == 113){ valeur de q et Q
            printf("DOMMAGE\n");
            game_delete(g);
            return EXIT_SUCCESS;
        }
    }
    if(game_nb_moves_cur(g)<=game_nb_moves_max(g)){
        printf("BRAVO\n");
        game_delete(g);
    }

    return EXIT_SUCCESS;

} */

 int play_recolor(game g){
    game_display(g);

    while (game_is_over(g)==false){
        char value= getchar();
        if ((value >= 48 && value <= 57)
        || (value>=97 && value <= 107)){ /*valeur de 1, 2, 3 et 0*/
            value=value-48;
            game_play_one_move(g, value);
            game_display(g);
        }
        /* Restart le jeu */
        if (value == 82 || value == 114){ /*valeur de r et R*/
            game_restart(g);
            game_display(g);
        }
        
        /* Quitter le jeu */
        if (value == 81 || value == 113){ /*valeur de q et Q*/
            printf("DOMMAGE\n");
            game_delete(g);
            return EXIT_SUCCESS;
        }
    }
    if(game_nb_moves_cur(g)<=game_nb_moves_max(g)){
        printf("BRAVO\n");
        game_delete(g);
    }
    game_delete(g);
    return EXIT_SUCCESS;

    }

int main(int argc, char *argv[]){
    if(argc==1){
        game g = game_default();
        play_recolor(g);
    }
    else { 
        game g = game_load(argv[1]);
        play_recolor(g);
   
    }
}

/* Laura ALANOIX */
/* Ayoub NOUAMANI*/
/* Eric JIN */