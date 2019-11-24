
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "game_io.h"


struct game_s {
    color *cell; //pointe vers la grille du jeu
    color *cell_init; //pointe vers la grille du jeu initiale
    uint nbmax; // nombre max de move
    uint nbmovecur; //nombre de mouvements actuel
};



game game_new(color *cells, uint nb_moves_max){
    game g=(game)malloc(sizeof(struct game_s));
    if (g==NULL){
        fprintf(stderr,"errrr");
        exit(1);
    }
    g->nbmax=nb_moves_max;
    g->nbmovecur=0;
    g->cell =(color*)malloc(SIZE*SIZE*sizeof(color));
     g->cell_init =(color*)malloc(SIZE*SIZE*sizeof(color));
     if (g->cell_init==NULL || g->cell==NULL){
         fprintf(stderr,"errror\n");
         exit(1);
     }
     for(int i=0;i<SIZE*SIZE;i++){
         g->cell[i]=cells[i];
         g->cell_init[i]=cells[i];
     }
    return g;
}


game game_new_empty(){
    game g=(game)malloc(sizeof(struct game_s));
    if (g==NULL){
        fprintf(stderr,"errrr\n");
        exit(1);
    }
    g->nbmax=12;
    g->nbmovecur=0;
    g->cell =(color*)malloc(SIZE*SIZE*sizeof(color));
     g->cell_init =(color*)malloc(SIZE*SIZE*sizeof(color));
     if (g->cell_init==NULL || g->cell==NULL){
         fprintf(stderr,"errror\n");
         exit(1);
     }
      for(int i=0;i<SIZE*SIZE;i++){
         g->cell_init[i]=0;
         g->cell[i]=0;
     }
    return g;
}


void game_set_cell_init(game g, uint x, uint y, color c){
    if(g==NULL){
        exit(EXIT_FAILURE);
    }
    if(c<0 || c>3 || x>=SIZE || y>=SIZE){
        exit(EXIT_FAILURE);
    }
  
    g->cell_init[(12*y)+x]=c;
    g->cell[(12*y)+x]=c;
           
    }


void game_set_max_moves(game g, uint nb_max_moves){
    if (g==NULL || nb_max_moves==0){
        fprintf(stderr,"not enogh memory!\n");
        exit (EXIT_FAILURE);
    }
    
    g->nbmax = nb_max_moves;

}


uint game_nb_moves_max(cgame g){
     if (g==NULL){
        fprintf(stderr,"not enogh memory!\n");
        exit (EXIT_FAILURE);
    }
    
    return g->nbmax;
}


color game_cell_current_color(cgame g, uint x, uint y){
     if (g==NULL||x>=SIZE||y>=SIZE){
        fprintf(stderr,"not enogh memory!\n");
        exit (EXIT_FAILURE);
    }
    return  g->cell[(SIZE*y)+x];
}

game game_copy(cgame g){
    if (g==NULL){
        fprintf(stderr, "POINTEUR null\n");
        exit(EXIT_FAILURE);
    }
    game game_copy = game_new_empty();
    for (int i=0; i < SIZE*SIZE; i++){
        game_copy->cell[i]=g->cell[i];
        game_copy->cell_init[i]=g->cell_init[i];
    }
    game_copy->nbmax=g->nbmax;
    game_copy->nbmovecur=g->nbmovecur;
    return game_copy;
}


uint game_nb_moves_cur(cgame g){
    if (g==NULL){
        fprintf(stderr, "POINTEUR null\n");
        exit(EXIT_FAILURE);
    }
    return g->nbmovecur;
}


void game_play_one_move(game g, color c){
    if (g==NULL){
        fprintf(stderr, "POINTEUR null\n");
        exit(EXIT_FAILURE);
    }
    if (c<0 || c>=NB_COLORS){
        fprintf(stderr, "Couleur innexistante\n");
        exit(EXIT_FAILURE);
    }
    uint valeur = game_cell_current_color(g,0,0);
    game_set_cell_init(g,0,0,c);
    if(valeur==game_cell_current_color(g,1,0)){
       game_set_cell_init(g,1,0,c);
    }
    for (uint x=0;x<SIZE-1;x++){
        for (uint y=1;y<SIZE-1;y++){
           
            if(game_cell_current_color(g,x,y)==valeur){
                if(game_cell_current_color(g,x,y)==game_cell_current_color(g,x,y+1)){
                    game_set_cell_init(g,x,y+1,c);
                    
                }
                game_set_cell_init(g,x,y,c);
               
                if(game_cell_current_color(g,x+1,y)==valeur){
                    game_set_cell_init(g,x+1,y,c);
                     if(game_cell_current_color(g,x+1,y+1)==valeur){
                    game_set_cell_init(g,x+1,y+1,c);
                    
                }
                }
                   
                valeur = game_cell_current_color(g,0,0);
          }  
          
        
            
            }

        }
    g->nbmovecur=g->nbmovecur+1;
}
    /* laura test
    uint valeur = game_cell_current_color(g,0,0);
    printf("%u %u %u\n",game_cell_current_color(g,0,0),game_cell_current_color(g,0,1),game_cell_current_color(g,0,2));
    ;
    uint i=0;
    while(g->cell[i]==valeur){

if(g->cell[i]==g->cell[i+1]&& i<SIZE*SIZE-1){
    g->cell[i+1]=c;

}
if(g->cell[i]==g->cell[i+12] && i<SIZE*SIZE-1){
    g->cell[i+12]=c;

}
i=i+12;

g->cell[0]=c;
valeur=game_cell_current_color(g,0,0);
    }


 g->nbmovecur=g->nbmovecur+1;

}
        
    */
    /* ayoub
        uint valeur= game_cell_current_color(g->cell, 0, 0);
        for (uint i=0; i>SIZE*SIZE; i++){
            if (g->tab[x]==true){
                if (x%SIZE==0){
                    if (x==0){
                        if (cell[x+1]==valeur){
                            tab[x+1]=true;
                        }
                        if (cell[x+SIZE]==valeur){
                            tab[x+SIZE]=true;
                        }
                    }
                    else if(x==SIZE*(SIZE-1)){
                        if (cell[x+1]==valeur){
                            tab[x+1]=true;
                        }
                        if (cell[x-SIZE]==valeur){
                            tab[x+SIZE]=true;
                        }
                    }else{
                        if (cell[x+1]==valeur){
                            tab[x+1]=true;
                        }
                        if (cell[x+SIZE]==valeur){
                            tab[x+SIZE]=true;
                        }
                        if (cell[x-SIZE]==valeur){
                            tab[x+SIZE]=true;
                        }
                    }
                }
                else if (x%SIZE>0 && x%SIZE<SIZE-1){
                    if (x<SIZE){
                        if (cell[x+1]==valeur){
                            tab[x+1]=true;
                        }
                        if (cell[x+SIZE]==valeur){
                            tab[x+SIZE]=true;
                        }
                        if (cell[x-1]==valeur){
                            tab[x+SIZE]=true;
                        }
                    }
                    else if (x>SIZE*(SIZE-1)){
                        if (cell[x+1]==valeur){
                            tab[x+1]=true;
                        }
                        if (cell[x-SIZE]==valeur){
                            tab[x+SIZE]=true;
                        }
                        if (cell[x-1]==valeur){
                            tab[x+SIZE]=true;
                        }
                    }else{
                        if (cell[x+1]==valeur){
                            tab[x+1]=true;
                        }
                        if (cell[x-SIZE]==valeur){
                            tab[x+SIZE]=true;
                        }
                        if (cell[x-1]==valeur){
                            tab[x+SIZE]=true;
                        }
                        if (cell[x+SIZE]==valeur){
                            tab[x+SIZE]=true;
                        }
                    }
                }else{
                    if (x==SIZE-1){
                        if (cell[x-1]==valeur){
                            tab[x+1]=true;
                        }
                        if (cell[x+SIZE]==valeur){
                            tab[x+SIZE]=true;
                        }
                    }//ici
                    else if (x==SIZE*SIZE-1){
                        if (cell[x-1]==valeur){
                            tab[x+1]=true;
                        }
                        if (cell[x-SIZE]==valeur){
                            tab[x+SIZE]=true;
                        }
                    }else{
                        if (cell[x-1]==valeur){
                            tab[x+1]=true;
                        }
                        if (cell[x+SIZE]==valeur){
                            tab[x+SIZE]=true;
                        }
                        if (cell[x-SIZE]==valeur){
                            tab[x+SIZE]=true;
                        }
                    }
                }
                g->cell[x]=c;
            }
        }
    }
    */


void game_delete(game g){
if(g==NULL){
    exit(EXIT_SUCCESS);
}
free(g->cell);
free(g->cell_init);
    free(g);
    g=NULL;
    }


bool game_is_over(cgame g){
   if(g==NULL){
       exit(EXIT_FAILURE);
   }
    if (g->nbmovecur>g->nbmax){
             return false;
         }
    for(int i=0;i<(SIZE*SIZE)-1;i++){
         if(g->cell[i]!=g->cell[i+1]){
    return false;
} 
}
return true;
 }


void game_restart(game g){
    if(g==NULL){
       exit(EXIT_FAILURE);
   }
    g->nbmovecur=0;
      for(int i=0;i<SIZE*SIZE;i++){
         g->cell[i]=g->cell_init[i];
    
     } 
    }

