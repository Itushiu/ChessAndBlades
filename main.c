#include "general_structures.h"

int init_chessboard(piece_t board[8][8]);
int print_board(piece_t board[8][8]);
int get_input(int move[4]);

int row;
int column;

int main(void) {

    piece_t board[8][8]; // create empty array 8x8 of piece_t [column][row]

    init_chessboard(board); // fill board with standard pieces
    
    print_board(board); // print board

    int move[4]; // create array for move in form {from_c, from_r, to_c, to_r}
    get_input(move); // get input in form A3 E4 and write it to array move

    return(0);
}

