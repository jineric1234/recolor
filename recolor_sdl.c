// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts     

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "game.h"
#include "game_io.c"
#include "game_io.h"
#include "game.h"
#include "game.c"
#include "recolor_sdl.h"

/* **************************************************************** */

#define FONT "Arial.ttf"
#define FONTSIZE 20
#define BACKGROUND "background.png"

/* **************************************************************** */
  /* PUT YOUR VARIABLES HERE */
     
struct Env_t {  
  SDL_Texture * grid;
  SDL_Texture * text;
  SDL_Texture * text2;

  game game_played;
}; 
     
/* **************************************************************** */
  /* PUT YOUR CODE HERE TO INIT TEXTURES, ... */
     
Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[])
{  
  Env * env = malloc(sizeof(struct Env_t));
  PRINT("To play you need to click in a case with color you want to play! \nWarning: you have a maximum of mouvements you can play.\n");
  PRINT("Good luck!\n");
  PRINT("Press ESC to quit\n");
  /*pointer with the gamme loaded*/ 
  env->game_played = game_load(argv[1]);

  /* init text texture using Arial font */
 
  char curmove[50]="";
  char nbmovemax[50]="";
 /* int tempsActuel=0, tempsPrecedent=0;*/

  SDL_Color color = { 0, 0, 0, 255 }; /* blue color in RGBA */
  TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
  TTF_Font * font2 = TTF_OpenFont(FONT, FONTSIZE);
  if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD);
  TTF_SetFontStyle(font2, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
  
  
  /*tempsActuel = SDL_GetTicks();*/
  sprintf(curmove,"moves played:%d",game_nb_moves_cur(env->game_played));
  SDL_Surface * surf = TTF_RenderText_Blended(font, curmove, color); // blended rendering for ultra nice text
  env->text = SDL_CreateTextureFromSurface(ren, surf);
 /* if((tempsActuel-tempsPrecedent) >= 100){
    sprintf(curmove,"moves played:%d",game_nb_moves_cur(env->game_played));
    SDL_FreeSurface(surf);
    env->text=SDL_CreateTextureFromSurface(ren, surf);
    tempsPrecedent=tempsActuel;
  }*/
 
 sprintf(nbmovemax,"move max:%d",game_nb_moves_max(env->game_played));
  /*env->text = TTF_RenderText_Shaded(font,curmove,color);*/
  SDL_Surface * surf2 = TTF_RenderText_Blended(font2, nbmovemax, color);
   env->text2 = SDL_CreateTextureFromSurface(ren, surf2);

  SDL_FreeSurface(surf);
  SDL_FreeSurface(surf2);
  TTF_CloseFont(font);
  return env;
}
     
/* **************************************************************** */
     
  /* PUT YOUR CODE HERE TO RENDER TEXTURES, ... */
void render(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
  SDL_Rect rect;
 
  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* render text texture */
  SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
  rect.x = 0; 
  rect.y = h-(h*0.05) - rect.h/2; 
  SDL_RenderCopy(ren, env->text, NULL, &rect);

  SDL_QueryTexture(env->text2, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2 - rect.w/2; 
  rect.y = h-(h*0.05) - rect.h/2; 
  SDL_RenderCopy(ren, env->text2, NULL, &rect);

  /* render a grid with lines */
  int height = env->game_played->height;
  int width = env->game_played->width;
  int case_h = (h-(h*0.1))/height;
  int case_w = w/width;

  /*grille exemple*/
  /*for (int i=1; i<10; i++){
    SDL_SetRenderDrawColor(ren, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(ren, 0, (i*100), w, (i*100));
    SDL_RenderDrawLine(ren,  (i*100),0,  (i*100), h);
  }*/
  for (int x=0; x<height; x++){
    for (int y=0; y<width; y++){
      int color = env->game_played->cell[x*width+y];
      
      //choise of the color based of the number of the case
      if(color == 0) SDL_SetRenderDrawColor(ren, 255, 0, 0, SDL_ALPHA_OPAQUE);/*RED */
      else if(color == 1) SDL_SetRenderDrawColor(ren, 0, 0, 255, SDL_ALPHA_OPAQUE);/*BLUE */
      else if(color == 2) SDL_SetRenderDrawColor(ren, 0, 128, 0, SDL_ALPHA_OPAQUE);/*GREEN */
      else if(color == 3) SDL_SetRenderDrawColor(ren, 255, 255, 0, SDL_ALPHA_OPAQUE);/*YELLOW */
      else if(color == 4) SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE); /*WHITE */
      else if(color == 5) SDL_SetRenderDrawColor(ren, 128, 0, 0, SDL_ALPHA_OPAQUE);/*MAROON */
      else if(color == 6) SDL_SetRenderDrawColor(ren, 153, 153, 255, SDL_ALPHA_OPAQUE);/* */
      else if(color == 7) SDL_SetRenderDrawColor(ren, 128, 128, 0, SDL_ALPHA_OPAQUE);/*OLIVE */
      else if(color == 8) SDL_SetRenderDrawColor(ren, 255, 0, 255, SDL_ALPHA_OPAQUE);/*FUCHSIA */
      else if(color == 9) SDL_SetRenderDrawColor(ren, 0, 255, 255, SDL_ALPHA_OPAQUE);/*AQUA */
      else if(color == 10) SDL_SetRenderDrawColor(ren, 0, 128, 128, SDL_ALPHA_OPAQUE);/*TEAL */
      else if(color == 11) SDL_SetRenderDrawColor(ren, 192, 192, 192, SDL_ALPHA_OPAQUE);/*SILVER */
      else if(color == 12) SDL_SetRenderDrawColor(ren, 0, 0, 128, SDL_ALPHA_OPAQUE);/*NAVY */
      else if(color == 13) SDL_SetRenderDrawColor(ren, 0, 255, 0, SDL_ALPHA_OPAQUE);/*LIME */
      else if(color == 14) SDL_SetRenderDrawColor(ren, 128, 128, 128, SDL_ALPHA_OPAQUE);/*GRAY */
      else if(color == 15) SDL_SetRenderDrawColor(ren, 128, 0, 128, SDL_ALPHA_OPAQUE);/*PURPLE */
      else {fprintf(stderr, "inexistant color!!\n");};
      
      //shape of the space  
      rect.x = y*case_w;
      rect.y = x*case_h;
      rect.w = w/width;
      rect.h = h/height;
      
      SDL_RenderFillRect(ren, &rect);
    }
  }
}
     
/* **************************************************************** */
     
     
bool process(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e)
{     

  if (e->type == SDL_QUIT) {
    return true;
  }

  /* PUT YOUR CODE HERE TO PROCESS EVENTS */
  else if (e->type == SDL_KEYDOWN) {
    switch (e->key.keysym.sym) {
    case  SDLK_0: game_play_one_move(env->game_played, 0); break;
    case  SDLK_1: game_play_one_move(env->game_played, 1); break;
    case  SDLK_2: game_play_one_move(env->game_played, 2); break;
    case  SDLK_3: game_play_one_move(env->game_played, 3); break;
    case  SDLK_4: game_play_one_move(env->game_played, 4); break;
    case  SDLK_5: game_play_one_move(env->game_played, 5); break;
    case  SDLK_6: game_play_one_move(env->game_played, 6); break;
    case  SDLK_7: game_play_one_move(env->game_played, 7); break;
    case  SDLK_8: game_play_one_move(env->game_played, 8); break;
    case  SDLK_9: game_play_one_move(env->game_played, 9); break;
    case  SDLK_a: game_play_one_move(env->game_played, 10); break;
    case  SDLK_b: game_play_one_move(env->game_played, 11); break;
    case  SDLK_c: game_play_one_move(env->game_played, 12); break;
    case  SDLK_d: game_play_one_move(env->game_played, 13); break;
    case  SDLK_e: game_play_one_move(env->game_played, 14); break;
    case  SDLK_f: game_play_one_move(env->game_played, 15); break;
    case  SDLK_r: game_restart(env->game_played); break;
    case SDLK_q:  return true; break;
    case SDLK_ESCAPE:  return true; break;      
    }
  }
  
  return false; 
}

/* **************************************************************** */

void clean(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
  /* PUT YOUR CODE HERE TO CLEAN MEMORY */
    SDL_DestroyTexture(env->text);
    game_delete(env->game_played);
    free(env);
}
     
/* **************************************************************** */
