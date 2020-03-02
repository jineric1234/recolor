#ifndef __RECOLOR_SOLVE__
#define __RECOLOR_SOLVE__
#include <stdio.h>
#include <stdbool.h>
#include "game.h"

/**
 * @file recolor_solve.h
 *
 * @brief This file provides functions to solved the game.
 *
 **/

/**
 * @brief Write the solution of the game
 * @param filename
 * @param tab
 * @param size_tab the size of the tab
 **/
void write_solution(char *filename,int *tab, int size_tab){


/**
 * @brief creates a tab
 * @param x
* @return the created tab
 **/
int* tab_move(int x);

/**
 * @brief true if..
 * @param x 
 **/
bool* tab_bool1(int x)


/**
 * @brief 
 * @return true, if ..
 * @param g the game
 * @pre @p g is a valid pointer toward a game structure
 **/
bool* near_move(game g);


/**
 * @brief Solve the game 
 * @param g
 * @param x
 * @param tabmove 
 * @param filename 

 **/
void solve_aux(game g, uint x, int *tabmove, char *filename );


/**
 * @brief allows to calculate a solution (if it exists) to the problem stored in the file
 * @param g
 * @param filename 
 * @pre @p g is a valid pointer toward a cgame structure

 **/
void FIND_ONE (game g, char *filename); 

/**
 * @brief find the number of solution (if it exists) to the problem stored in the file
 * @param g
 * @param filename 
 * @pre @p g is a valid pointer toward a cgame structure

 **/
void NB_SOL (game g, char *filename);

/**
 * @brief allows to calculate a solution with the smallest number of movements to the problem stored in the file
 * @param g
 * @param filename 
 * @pre @p g is a valid pointer toward a cgame structure

 **/
void FIND_MIN (game g, char*filename);


#endif  // RECOLOR_SOLVE_H