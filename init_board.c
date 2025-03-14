#include "general_structures.h"

int init_chessboard(piece_t board[8][8]) {

    extern int column;
    extern int row;

    // 8x8 board with empty pieces
    for (column = 0; column < 8; column++) {         
        for (row = 0; row < 8; row++) {
            board[column][row].type = ' ';
            board[column][row].color = ' ';
            board[column][row].hp = ' ';
            board[column][row].attack = ' ';
            board[column][row].defence = ' ';
            board[column][row].ultimate = 0;

        }
    }

    // all pieces with standard positions
    for (column = 0; column < 8; column++) {
        board[column][1].type = 'P'; // P = Pawn
        board[column][1].hp = 5;
        board[column][1].attack = 2;
        board[column][1].defence = 2;
        board[column][1].ultimate = 1;

        board[column][6].type = 'P';
        board[column][6].hp = 5;
        board[column][6].attack = 2;
        board[column][6].defence = 2;
        board[column][6].ultimate = 1;
    }

    board[0][0].type = 'R'; // R = Rook
    board[0][0].hp = 8;
    board[0][0].attack = 2;
    board[0][0].defence = 4;
    board[0][0].ultimate = 1;

    board[0][7].type = 'R';
    board[0][7].hp = 8;
    board[0][7].attack = 2;
    board[0][7].defence = 4;
    board[0][7].ultimate = 1;

    board[7][0].type = 'R';
    board[7][0].hp = 8;
    board[7][0].attack = 2;
    board[7][0].defence = 4;
    board[7][0].ultimate = 1;
    
    board[7][7].type = 'R';
    board[7][7].hp = 8;
    board[7][7].attack = 2;
    board[7][7].defence = 4;
    board[7][7].ultimate = 1;


    board[3][0].type = 'Q'; // Q = Queen
    board[3][0].hp = 3;
    board[3][0].attack = 7;
    board[3][0].defence = 1;
    board[3][0].ultimate = 1;
    
    board[3][7].type = 'Q';
    board[3][7].hp = 3;
    board[3][7].attack = 7;
    board[3][7].defence = 1;
    board[3][7].ultimate = 1;


    board[4][0].type = 'K'; // K = King
    board[4][0].hp = 10;
    board[4][0].attack = 5;
    board[4][0].defence = 0;
    board[4][0].ultimate = 1;

    board[4][7].type = 'K';
    board[4][7].hp = 10;
    board[4][7].attack = 5;
    board[4][7].defence = 0;
    board[4][7].ultimate = 1;


    board[1][0].type = 'H'; // H = Knight (Horse)
    board[1][0].hp = 4;
    board[1][0].attack = 4;
    board[1][0].defence = 2;
    board[1][0].ultimate = 1;

    board[6][0].type = 'H';
    board[6][0].hp = 4;
    board[6][0].attack = 4;
    board[6][0].defence = 2;
    board[6][0].ultimate = 1;

    board[1][7].type = 'H';
    board[1][7].hp = 4;
    board[1][7].attack = 4;
    board[1][7].defence = 2;
    board[1][7].ultimate = 1;

    board[6][7].type = 'H';
    board[6][7].hp = 4;
    board[6][7].attack = 4;
    board[6][7].defence = 2;
    board[6][7].ultimate = 1;


    board[2][0].type = 'B'; // B = Bishop
    board[2][0].hp = 3;
    board[2][0].attack = 4;
    board[2][0].defence = 2;
    board[2][0].ultimate = 1;

    board[5][0].type = 'B';
    board[5][0].hp = 3;
    board[5][0].attack = 4;
    board[5][0].defence = 2;
    board[5][0].ultimate = 1;

    board[2][7].type = 'B';
    board[2][7].hp = 3;
    board[2][7].attack = 4;
    board[2][7].defence = 2;
    board[2][7].ultimate = 1;

    board[5][7].type = 'B';
    board[5][7].hp = 3;
    board[5][7].attack = 4;
    board[5][7].defence = 2;
    board[5][7].ultimate = 1;
    
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