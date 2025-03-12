#include "general_structures.h"

int init_chessboard(piece_t board[8][8]) {

    extern int column;
    extern int row;

    // 8x8 board with empty pieces
    for (column = 0; column < 8; column++) {         
        for (row = 0; row < 8; row++) {
            board[column][row].type = ' ';
            board[column][row].color = ' ';
        }
    }

    // all pieces with standard positions
    for (column = 0; column < 8; column++) {
        board[column][1].type = 'P'; // P = Pawn
        board[column][6].type = 'P';
    }

    board[0][0].type = 'R'; // R = Rook
    board[0][7].type = 'R';
    board[7][0].type = 'R';
    board[7][7].type = 'R';

    board[3][0].type = 'Q'; // Q = Queen
    board[3][7].type = 'Q';

    board[4][0].type = 'K'; // K = King
    board[4][7].type = 'K';

    board[1][0].type = 'H'; // H = Knight (Horse)
    board[6][0].type = 'H';
    board[1][7].type = 'H';
    board[6][7].type = 'H';

    board[2][0].type = 'B'; // B = Bishop
    board[5][0].type = 'B';
    board[2][7].type = 'B';
    board[5][7].type = 'B';
    
    // black color for last two rows
    for (row = 6; row < 8; row++) {
        for (column = 0; column < 8; column++) {
            board[column][row].color = 'b';
        }
    }

    // white color for first two rows
    for (row = 0; row < 2; row++) {
        for (column = 0; column < 8; column++) {
            board[column][row].color = 'w';
        }
    }
    
    return(0);

}