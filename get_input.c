#include <stdio.h>
#include "general_structures.h"

int get_input(int move[4], piece_t board[8][8], char current_player) {

    char from_c, from_r, to_c, to_r;

    jump_get_input:

    from_c = ' ';
    from_r = ' '; 
    to_c = ' '; 
    to_r = ' ';

    if (current_player == 'w') {
        printf("Player White input your move (E.g. A3 E4): ");
    } else {
        printf("Player Black input your move (E.g. A3 E4): ");
    }

    scanf(" %c%c %c%c", &from_c, &from_r, &to_c, &to_r); // get 4 characters from input
    
    // check if valid input
    if ((from_c < 'A' || from_c > 'H') || (from_r < '1' || from_r > '8') || (to_c < 'A' || to_c > 'H') || (to_r < '1' || to_r > '8')) {
        printf("False input, try again!\n");
        goto jump_get_input;
    }

    // turn these characters to int and fill the move array with them
    move[0] = from_c-65;
    move[1] = from_r-49;
    move[2] = to_c-65;
    move[3] = to_r-49;

    // check if not empty figure
    if (board[move[0]][move[1]].type == ' ') {
        printf("You can't move empty space, try again!\n");
        goto jump_get_input;
    }

    // check if your figure
    if (current_player != board[move[0]][move[1]].color) {
        printf("Not your figure, try again!\n");
        goto jump_get_input;
    }

    return(0);
}