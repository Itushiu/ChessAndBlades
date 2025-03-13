#include "general_structures.h"
#include <stdio.h>

int print_board(piece_t board[8][8]);
int *find_my_king(piece_t board[8][8], char my_color);
//TODO; ITS FAKE
int is_king_attacked(int my_king[2], piece_t board [8][8]);
//TODO; ITS FAKE
int legal_moves (/*no f idea yet*/);

int make_move(piece_t board [8][8], int move[4]){

	//store the move in case of return
	piece_t from = board[move[0]][move[1]];
	piece_t to = board[move[2]][move[3]];


	
	//move the pieces
	board[move[2]][move[3]] = board[move[0]][move[1]];
	board[move[0]][move[1]].type = ' ';  // make empty cell "from".type
	board[move[0]][move[1]].color = ' '; // make empty cell "from".color
	
	print_board(board);	
	
	char my_color = from.color;

	if (to.type == 'K'){
		printf("GAME OVER, PLAYER %c WINS\n", my_color);
		return 1;
	}
	int *my_king = find_my_king(board, my_color);
	if (is_king_attacked(my_king, board)){
		//CHECK -->
		// go back
		board[move[0]][move[1]] = from;
		board[move[2]][move[3]] = to;
		if (legal_moves()){
			printf("CHECK");
			return 0; // back to game but next player have limited play range CHECK
		}
		else {
			// legal_moves return 0
			printf("CHECKMATE");
			return 1; //end of game
		}
	}
	else {
		if (legal_moves()){
			printf("NEXT MOVE");
			return 0 ; // continue game
		}
		else {
			printf("STALEMATE");
			return 1 ; //end game via STALEMATE
		}
	}
}

			// IF (legal_moves to make (is_king_attacked == 0) EXIST 
					// CHECK & U HAVE TO MAKE CORRECT MOVE
					// IF (legal_moves to make (is_king_attacked == 0) DOESN'T EXIST
					// CHECKMATE
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


int *find_my_king(piece_t board[8][8], char my_color){
	//column rows as coordinates
	int k_r = -1;
	int my_king[2];
	for (int c = 0; c < 8; c++) {
		for (int r = 0; r < 8; r++) {
			if (board[c][r].type == 'K' && board[c][r].color == my_color) {
				my_king[0] = c;
				my_king[1] = r; //like .k [k_c][k_r]
				k_r++;
				break;
			}
		}
	return (my_king);
	//if (k_r == -1)
	//	break;
	}
}

int is_king_attacked(int my_king[2], piece_t board [8][8]){
	return 0; // no its not
	//return 1; // yes it is
}

int legal_moves (/*no f idea yet*/) {
	// maybe check is_king_attacked
	return 1; // there are some CONTINUE
	//return 0; // there are none GAME OVER
}