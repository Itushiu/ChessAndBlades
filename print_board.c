#include "general_structures.h"
#include <stdio.h>

int print_board(piece_t board[8][8]) {

    extern int column;
    extern int row;

    // print board
    for (column = 7; column >= 0; column--) {
        printf("%d ", column+1);
        for (row = 0; row < 8; row++) {
            printf("[%c-%c]", board[column][row].type, board[column][row].color);
        }
        printf("\n");
    }
    for (row = 0; row < 8; row++) {
        printf("    %c", row+65);
    }
    printf("\n");

    return(0);
}