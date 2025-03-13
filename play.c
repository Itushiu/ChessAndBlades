#include "general_structures.h"
#include <stdio.h>

int init_chessboard(piece_t board[8][8]);	// start of the game, pieces on initial positions
											// return 0 (can be void)
int print_board(piece_t board[8][8]);		// print the current state of the board
											// return 0 (can be void)
int get_input(int move[4], piece_t board[8][8], char current_player);// read user input & fill move with [from_c, from_r, to_c, to_r]
											// return 0 (can be void)
//TO_DO:
int validate_moves(piece_t board[8][8], int move[4]);

int make_move(piece_t board [8][8], int move[4]);

int game_state(piece_t board[8][8], char current_player); //the same parts as in "check on king"
				// but here we have to analise is it even NEEDED to start next iteration?
				// or can we say that the current player won and that s it????

int row;
int column;

int main(void) {

	piece_t board[8][8]; // create empty array 8x8 of piece_t [column][row]
	init_chessboard(board); // fill board with pieces on initial positions
	print_board(board); // print board
	int move [4];
	char current_player = 'w';

	while (1) {
		// do i have my king?
		get_input(move, board, current_player);								// succesfull input
		if (validate_moves(board, move)) {					// knows the rules
			// TODO: ugly, change later "don't eat your team"
			if (!(board[move[2]][move[3]].type != ' ' && board[move[2]][move[3]].color == board[move[0]][move[1]].color)){
				if(make_move(board, move) == 1){
					break;
				}
				//print_board(board);								// SDL?
			//if (game_state(board, current_player)) break;	// win/lose/draw
				current_player = (current_player == 'w') ? 'b' : 'w'; // switch 
			}
			else 
				printf("Don't eat your team\n");
		}
		else {
			printf("Not a valid move for %c\n", board[move[0]][move[1]].type);
		}
	}
	return 0;
}


int 
