#include "general_structures.h"


int init_chessboard(piece_t board[8][8]);	// start of the game, pieces on initial positions
											// return 0 (can be void)
int print_board(piece_t board[8][8]);		// print the current state of the board
											// return 0 (can be void)
int get_input(int move[4]);					// read user input & fill move with [from_c, from_r, to_c, to_r]
											// return 0 (can be void)
//TO_DO:
int validate_moves (piece_t board[8][8], int move[4]) 
	// char get_piece (move[4], board) 
	// has all the rules about movement, if else compare the pieces and call appropriate function
	// RULES ALREADY DONE, ALMOST ALL SAME FOR DECLARING
	int validate_move_X(int move [4])

int make_move(piece_t board [8][8], int move[4])
	//- dont spoil the situation yourself (check newly forbidden moves)
		// F is_under_attack(position_my_king)?
			// YES
			// F are there some legal moves to become safe again?
				//YES
				// if there are some, store the wrong SMTH IDK, dont use these cells, or 
				// like u have to move AWAY from this place blah blah
				// "CHECK"

				// NO
				// "CHECKMATE" 
			// NO
			//are there legal_moves? (+ count from last eaten piece/ amount of pieces on the board)
				// YES
					//next move player change blah blah
				// NO
					// DRAW IT IS
// like this smth idk??
//___ king_is_safe(piece_t piece.type == 'K')

int game_state(piece_t board[8][8], char current_player); the same parts as in "check on king"
				// but here we have to analise is it even NEEDED to start next iteration?
				// or can we say that the current player won and that s it????






int row;
int column;

int main(void) {

	piece_t board[8][8]; // create empty array 8x8 of piece_t [column][row]
	init_chessboard(board); // fill board with pieces on initial positions
	print_board(board); // print board
	int move [4];
	//TODO:
	char current_player = 'w';

	while (/*smth maybe simple 1, but ehhh*/) {
	if (get_move(move)) {									// succesfull input
		if (validate_moves(board, move)) {					// knows the rules
			make_move(board, move);							// TODO: check on king situation
			print_board(board);								// SDL?
			if (game_state(board, current_player)) break;	// win/lose/draw
			current_player = (current_player == 'w') ? 's' : 'w'; // switch 
		}
	}
}
return 0;
}
	}

