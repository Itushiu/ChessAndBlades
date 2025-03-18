#ifndef FUNCTIONS
#define FUNCTIONS

#include "general_structures.h"

//libraries for code
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

//libraries for SDL
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
 
//from new_play
//backend chess board
int init_chessboard(piece_t board[8][8]);
//has to be changed to the new one
int get_input(int move[4], piece_t board[8][8], char current_player); 
//rules of basic moves
int validate_moves(piece_t board[8][8], int move[4]);
//move pieces to upd backend board
int make_move(piece_t board[8][8], int move[4]);
//rules of ultimate abilities
int ultimate_abilities(int move[4], piece_t board[8][8], char *current_player);

//functions that initiate board, starting position for pieces & rand with the textRec on the right
int SDL_init_board(void);
int SDL_init_chess_figures(void);
int SDL_init_text(void);

// sdl fucntion that updates the position of pieces during the game
int SDL_pieces(piece_t board[8][8]);

int SDL_render (piece_t board [8][8]); // for render

void text_box_add(text_box_t *text_box, const char* text); // for text log, use: text_box_add(&text_box, "blabla");

#endif