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
    for (row = 0; row < 8; row++) {
        board[1][row].type = 'P'; // P = Pawn
        board[6][row].type = 'P';
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
    
    // black color for last two columns
    for (column = 6; column < 8; column++) {
        for (row = 0; row < 8; row++) {
            board[column][row].color = 'b';
        }
    }

    // white color for first two columns
    for (column = 0; column < 2; column++) {
        for (row = 0; row < 8; row++) {
            board[column][row].color = 'w';
        }
    }
    
    return(0);

}