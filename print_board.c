#include "general_structures.h"
#include <stdio.h>

extern int column;
extern int row;

int print_board(piece_t board[8][8]) {

    // print board
    printf("\n ");
    for (column = 0; column < 8; column++) {
        printf("   %c", column+65);
    }
    printf("\n");
    for (row = 7; row >= 0; row--) {
        printf("  +---+---+---+---+---+---+---+---+\n");
        printf("%d ", row+1);
        for (column = 0; column < 8; column++) {
            printf("|%c %c", board[column][row].type, board[column][row].color);
        }
        printf("|");
        printf(" %d", row+1);
        printf("\n");
    }
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf(" ");
    for (column = 0; column < 8; column++) {
        printf("   %c", column+65);
    }
    printf("\n\n");

    return(0);
}