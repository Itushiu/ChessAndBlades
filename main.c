#include "general_structures.h"

int init_chessboard(piece_t board[8][8]);
int print_board(piece_t board[8][8]);

int row;
int column;

int main(void) {

    piece_t board[8][8]; // create empty array 8x8 of piece_t

    init_chessboard(board); // fill board with standard pieces
    
    print_board(board); // print board
}