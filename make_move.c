#include "general_structures.h"
int *find_my_king(piece_t board[8][8], char my_color);
int is_king_attacked(int my_king[2], /*maybe board waity waity*/);

int make_move(piece_t board [8][8], int move[4]){
	char my_color = board[move[0]][move[1]];
	int *my_king = find_my_king(board);
	if (is_king_attacked(my_king)){
		// IF (legal_moves to make (is_king_attacked == 0) EXIST 
		// CHECK & U HAVE TO MAKE CORRECT MOVE
		// IF (legal_moves to make (is_king_attacked == 0) DOESN'T EXIST
		// CHECKMATE
	 
	}


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

}

int *find_my_king(piece_t board[8][8], char my_color){
	//column rows as coordinates
	int k_r = -1, k_c = -1;
	int *my_king[2];
	for (int c = 0; c < 8; c++) {
		for (int r = 0; r < 8; r++) {
			if (board[c][r].type == 'K' && board[c][r].color == my_color) {
				my_king[0] = c;
				my_king[1] = r; //like .k [k_c][k_r]
				break;
			}
		}
	return (my_king);
		//if (k_r != -1)
		//	break;

}