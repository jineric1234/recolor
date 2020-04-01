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
#include "game_rand.h"
#include "game_rand.c"


/* **************************************************************** */

#define FONT "Arial.ttf"
#define FONTSIZE 36
#define BACKGROUND "background.png"

/* **************************************************************** */
  /* PUT YOUR VARIABLES HERE */
     
struct Env_t {  
  SDL_Texture * grid;
  SDL_Texture * text;
  SDL_Texture * lose;
  SDL_Texture * victory;
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
  if (argc == 1){
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
    env->game_played = game_new_ext(SIZE, SIZE, cell, 12, false);
  }
  else if (argc == 2) env->game_played = game_load(argv[1]); 
  else if (argc <= 4){
    int width,height,nbmaxmove;
    sscanf(argv[1],"%d",&width);
    sscanf(argv[2],"%d",&height);
    sscanf(argv[3],"%d",&nbmaxmove);
    env->game_played = game_random_ext(width,height, false, 4,nbmaxmove);
  }
  else if (argc == 5){
    int width,height,nbmaxmove, nbcolors;
    sscanf(argv[1],"%d",&width);
    sscanf(argv[2],"%d",&height);
    sscanf(argv[3],"%d",&nbmaxmove);
    sscanf(argv[4],"%d",&nbcolors);
    env->game_played = game_random_ext(width,height, false, nbcolors, nbmaxmove);
  }
  else{
    int width,height,nbmaxmove,nbcolor;
    char wrapping;
    sscanf(argv[1],"%d",&width);
    sscanf(argv[2],"%d",&height);
    sscanf(argv[3],"%d",&nbmaxmove);
    sscanf(argv[4],"%d",&nbcolor);
    sscanf(argv[5],"%c",&wrapping);
    bool wrapping_g;
    if (wrapping=='S') wrapping_g = true;
    else wrapping_g = false;
    //argv[1], argv[2], wrapping, argv[4], argv[3]
    env->game_played = game_random_ext(width,height,wrapping_g,nbcolor,nbmaxmove);
  }

  TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
  if(!font) ERROR("TTF_OpenFont: %s\n", FONT);

  
  /*TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
  SDL_Surface * surf = TTF_RenderText_Blended(font, "YOU LOSE!", color); // blended rendering for ultra nice text
  env->lose = SDL_CreateTextureFromSurface(ren, surf);
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);*/

  /*env->victory=NULL;
  SDL_Color color1 = { 0, 0, 0, 0};
  TTF_Font * font1 = TTF_OpenFont(FONT, FONTSIZE);
  if(!font1) ERROR("TTF_OpenFont: %s\n", FONT);
  TTF_SetFontStyle(font1, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
  SDL_Surface * surf1 = TTF_RenderText_Blended(font1, "YOU WIN!", color1); // blended rendering for ultra nice text
  env->victory = SDL_CreateTextureFromSurface(ren, surf1);
  SDL_FreeSurface(surf1);
  TTF_CloseFont(font1);*/
  
  return env;
}
     
/* **************************************************************** */
     
  /* PUT YOUR CODE HERE TO RENDER TEXTURES, ... */
void render(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
  SDL_Rect rect;
  SDL_Rect rect1;
  SDL_Rect rect2;

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  //render text texture 
  SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2 - rect.w/2; 
  rect.y = h-(h*0.05) - rect.h/2; 
  SDL_RenderCopy(ren, env->text, NULL, &rect);


  /* render a grid with lines */
  int height = env->game_played->height;
  int width = env->game_played->width;
  int case_h = (h-(h*0.1))/height;
  int case_w = w/width;

  /*grille exemple*/
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
      
      //shape of the space  
      rect.x = y*case_w;
      rect.y = x*case_h;
      rect.w = w/width;
      rect.h = h/height;
      
      SDL_RenderFillRect(ren, &rect);
    }

  //render victory text texture 
  SDL_QueryTexture(env->victory, NULL, NULL, &rect1.w, &rect1.h);
  rect1.x = w/2 - rect1.w/2; 
  rect1.y = h/2 - rect1.h/2; 
  SDL_RenderCopy(ren, env->victory, NULL, &rect1);

  // render lose text texture
  SDL_QueryTexture(env->lose, NULL, NULL, &rect2.w, &rect2.h);
  rect2.x = w/2 - rect2.w/2; 
  rect2.y = h/2 - rect2.h/2; 
  SDL_RenderCopy(ren, env->lose, NULL, &rect2);
  }
}
     
/* **************************************************************** */
     
     
bool process(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e)
{     
  char curmove[50]="";

  /* text with score */
  SDL_Color color = { 0, 0, 0, 255 }; /* blue color in RGBA */
  TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
  if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
  int max = game_nb_moves_max(env->game_played);
  int current = game_nb_moves_cur(env->game_played);
  sprintf(curmove,"moves played:%d / %d",current, max);
  SDL_Surface * surf = TTF_RenderText_Blended(font, curmove, color); // blended rendering for ultra nice text
  env->text = SDL_CreateTextureFromSurface(ren, surf);
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);

//text victoire defaite
if (game_is_over(env->game_played)&& (current <= max)){
    SDL_Color color1 = { 0, 0, 0, 128 };
    TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
    SDL_Surface * surf2 = TTF_RenderText_Blended(font, "YOU WIN!", color1); // blended rendering for ultra nice text
    env->victory = SDL_CreateTextureFromSurface(ren, surf2);
    SDL_FreeSurface(surf2);
    TTF_CloseFont(font);
  }
if (!game_is_over(env->game_played) && current > max && env->victory==NULL){
    SDL_Color color2 = { 0, 0, 0, 255 };
    TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
    SDL_Surface * surf3 = TTF_RenderText_Blended(font, "YOU LOSE", color2); // blended rendering for ultra nice text
    env->lose = SDL_CreateTextureFromSurface(ren, surf3);
    SDL_FreeSurface(surf3);
    TTF_CloseFont(font);
  }

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
    case  SDLK_r: {
      game_restart(env->game_played); 
      env->victory=NULL;
      env->lose=NULL;    
      
      break;
    }
    case SDLK_q:  return true; break;
    case SDLK_ESCAPE:  return true; break;     
    }

  }
  else if (e->type == SDL_MOUSEBUTTONDOWN) {
    SDL_Point mouse; 
    SDL_GetMouseState(&mouse.x, &mouse.y);    
    int w, h, x_m, y_m;
    SDL_GetWindowSize(win, &w, &h);
    if (mouse.y<(h-h*0.1)){
      int x_case = w/(env->game_played->width);
      int y_case = (h-(h*0.1))/(env->game_played->height);
      x_m = mouse.x/x_case;
      y_m = mouse.y/y_case;
      int c = game_cell_current_color(env->game_played,x_m,y_m);
      if (c!=game_cell_current_color(env->game_played,0,0)) game_play_one_move(env->game_played,c);
    }
  }
  
  return false; 
}

/* **************************************************************** */

void clean(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
  /* PUT YOUR CODE HERE TO CLEAN MEMORY */
    SDL_DestroyTexture(env->text);
    SDL_DestroyTexture(env->lose);
    SDL_DestroyTexture(env->victory);
    SDL_DestroyTexture(env->grid);
    game_delete(env->game_played);
    free(env);
}
     
/* **************************************************************** */
