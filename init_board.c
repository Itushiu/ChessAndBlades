#include "general_structures.h"

int init_chessboard(piece_t board[8][8]) {

    extern int row;
    extern int column;

    // 8x8 board with empty pieces
    for (row = 0; row < 8; row++) {         
        for (column = 0; column < 8; column++) {
            board[row][column].type = ' ';
            board[row][column].color = ' ';
        }
    }

    // all pieces with standard positions
    for (column = 0; column < 8; column++) {
        board[1][column].type = 'P'; // P = Pawn
        board[6][column].type = 'P';
    }

    board[0][0].type = 'R'; // R = Rook
    board[0][7].type = 'R';
    board[7][0].type = 'R';
    board[7][7].type = 'R';

    board[0][3].type = 'Q'; // Q = Queen
    board[7][3].type = 'Q';

    board[0][4].type = 'K'; // K = King
    board[7][4].type = 'K';

    board[0][1].type = 'H'; // H = Knight (Horse)
    board[7][1].type = 'H';
    board[0][6].type = 'H';
    board[7][6].type = 'H';

    board[0][2].type = 'B'; // B = Bishop
    board[7][2].type = 'B';
    board[0][5].type = 'B';
    board[7][5].type = 'B';
    
    // black color for last two rows
    for (row = 6; row < 8; row++) {
        for (column = 0; column < 8; column++) {
            board[row][column].color = 's';
        }
    }

    // white color for first two rows
    for (row = 0; row < 2; row++) {
        for (column = 0; column < 8; column++) {
            board[row][column].color = 'w';
        }
    }
    
    return(0);

}