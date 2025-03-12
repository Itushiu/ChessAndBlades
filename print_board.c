#include "general_structures.h"
#include <stdio.h>

int print_board(piece_t board[8][8]) {

    extern int column;
    extern int row;

    // print board
    for (row = 7; row >= 0; row--) {
        printf("%d ", row+1);
        for (column = 0; column < 8; column++) {
            printf("[%c-%c]", board[column][row].type, board[column][row].color);
        }
        printf("\n");
    }
    for (column = 0; column < 8; column++) {
        printf("    %c", column+65);
    }
    printf("\n");

    return(0);
}