#include "functions.h"
#include "general_structures.h"

extern text_box_t text_box;
extern char text_box_buffer[500];

int print_board(piece_t board[8][8]);

int calculate_attack(piece_t board [8][8], int move[4]); // here is where the actual move is happening

int make_move(piece_t board [8][8], int move[4]){

	//store the move in case of return
	piece_t from = board[move[0]][move[1]];
	piece_t to = board[move[2]][move[3]];

	int move_result = calculate_attack(board, move); // returns 1 if my enemy died, 2 if my figure died, 0 otherwise 
	
	SDL_render (board);
	
	char my_color = from.color;
	char enemy_color = to.color;

	if (to.type == 'K' && move_result == 1){
		snprintf(text_box_buffer, 500, "GAME OVER, PLAYER %c WINS!", my_color);
        text_box_add(&text_box, text_box_buffer);
		return 1;
	}

	if (from.type == 'K' && move_result == 2){
		snprintf(text_box_buffer, 500, "GAME OVER, PLAYER %c WINS!", enemy_color);
        text_box_add(&text_box, text_box_buffer);
		return 1;
	}

	return 0;

}