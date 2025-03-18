#include "functions.h"
#include "general_structures.h"

int input_check(int input_value) { // clears input buffer and checks for EOF. Returns 1 if correct input
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // clear input buffer
     
    if (input_value == EOF) { // if EOF detected as input (e.g. Ctrl + D)
        printf("\nInput error! Try again!\n");
        clearerr(stdin); // remove EOF from input buffer
        return 0;
    }        
    return 1;
}

int get_input(int move[4], piece_t board[8][8], char current_player) {

    char from_c, from_r, to_c, to_r, move_check;
    int ultimate;
    char * ultimate_description;
    int input_value;

jump_get_input:

    from_c = ' ';
    from_r = ' '; 
    to_c = ' '; 
    to_r = ' ';
    move_check = ' ';
    ultimate = 0;

    if (current_player == 'w') {
        printf("Player White input your move (E.g. A2 A4 or E1 UT for ultimate): ");
    } else {
        printf("Player Black input your move (E.g. A2 A4 or E1 UT for ultimate): ");
    }

    input_value = scanf(" %c%c %c%c", &from_c, &from_r, &to_c, &to_r); // get 4 characters from input
    if (!input_check(input_value)) goto jump_get_input; // check for EOF, clear input buffer

    // check if ultimate skill
    if (('A' <= from_c && from_c <= 'H') && ('1' <= from_r && from_r <= '8') && to_c == 'U' && to_r == 'T') {
        ultimate = 1;
    }
    // check if valid input
    else if ((from_c < 'A' || from_c > 'H') || (from_r < '1' || from_r > '8') || (to_c < 'A' || to_c > 'H') || (to_r < '1' || to_r > '8')) {
        printf("False input, try again!\n");
        goto jump_get_input;
    }

    // turn these characters to int and fill the move array with them
    move[0] = from_c-'A'; // ascii leters A-H to 0-7 integers
    move[1] = from_r-'1'; // ascii numbers 1-8 to 0-7 integers
    move[2] = to_c-'A';
    move[3] = to_r-'1';

    // check if not empty figure
    if (board[move[0]][move[1]].type == ' ') {
        printf("You can't play empty space, try again!\n");
        goto jump_get_input;
    }

    // check if your figure
    if (current_player != board[move[0]][move[1]].color) {
        printf("Not your figure, try again!\n");
        goto jump_get_input;
    }

    if (ultimate == 1) goto jump_get_input_ultimate;

    // check if you actually move
    if (move[0] == move[2] && move[1] == move[3]) {
        printf("You can't move to the same place, try again!\n");
        goto jump_get_input;
    }

	if (board[move[2]][move[3]].type != ' ' && board[move[2]][move[3]].color == board[move[0]][move[1]].color) { // check if tried to attack your team
        printf("Don't eat your team! Try again!\n");
        goto jump_get_input;
    }

    if (board[move[2]][move[3]].type == ' ') { // move to empty space
        printf("You want to move your %c (HP: %d, ATT: %d, DEF: %d) to %c%c. Correct?\n", // show piece stats and check if sure
                board[move[0]][move[1]].type, board[move[0]][move[1]].hp, board[move[0]][move[1]].attack, board[move[0]][move[1]].defence, 
                to_c, to_r);
        
    jump_get_input2:
        printf("Y for Yes, N for No: ");
        input_value = scanf(" %c", &move_check);
        if (!input_check(input_value)) goto jump_get_input2; // check for EOF, clear input buffer
        if (move_check == 'N') goto jump_get_input;
        else if (move_check == 'Y') return(1); // returns 1 if normal move made
        else {
            printf("False input, try again!\n");
            goto jump_get_input2;
        }
    }
    
    else { // attack another piece
        printf("You want to attack enemy %c (HP: %d, ATT: %d, DEF: %d) with your %c (HP: %d, ATT: %d, DEF: %d). Correct?\n", // show pieces stats and check if sure
            board[move[2]][move[3]].type, board[move[2]][move[3]].hp, board[move[2]][move[3]].attack, board[move[2]][move[3]].defence,
            board[move[0]][move[1]].type, board[move[0]][move[1]].hp, board[move[0]][move[1]].attack, board[move[0]][move[1]].defence);
    
    jump_get_input3:
        printf("Y for Yes, N for No: ");
        input_value = scanf(" %c", &move_check);
        if (!input_check(input_value)) goto jump_get_input3; // check for EOF, clear input buffer
        if (move_check == 'N') goto jump_get_input;
        else if (move_check == 'Y') return(1); // returns 1 if normal move made
        else {
            printf("False input, try again!\n");
            goto jump_get_input3;
        }
    }

jump_get_input_ultimate: // following for ultimate check

    if (board[move[0]][move[1]].ultimate == 0) {
        printf("You already used the ultimate ability for this piece! Try again!\n");
        goto jump_get_input;
    }

    switch (board[move[0]][move[1]].type) { // write the ultimate description for current piece for later use
        case 'P':
            ultimate_description = "Pawn Transform (only available after reaching the end of the board)";
            break;
        case 'Q':
            ultimate_description = "Double Attack (try to attack two pieces in single turn, separate rolls for each attack)";
            break;
        case 'K':
            ultimate_description = "King Escape (teleport your king to random free tile)";
            break;
        case 'B':
            ultimate_description = "Bishop as King (move once using the same rules as King, cannot be an attack)";
            break;
        case 'R':
            ultimate_description = "Rook the Shield (redirects next attack of your opponent to itself and blocks any ultimate while active)";
            break;
        case 'H':
            ultimate_description = "Double Jump (two jumps in one turn, first one can't be an attack)";
            break;
    }

    printf("You want to use the ultimate ability of your %c (HP: %d, ATT: %d, DEF: %d).\nIt is %s. Correct?\n", // show piece stats and ultimate and check if sure
        board[move[0]][move[1]].type, board[move[0]][move[1]].hp, board[move[0]][move[1]].attack, board[move[0]][move[1]].defence, 
        ultimate_description);

jump_get_input4:
    printf("Y for Yes, N for No: ");
    input_value = scanf(" %c", &move_check);
    if (!input_check(input_value)) goto jump_get_input4; // check for EOF, clear input buffer
    if (move_check == 'N') goto jump_get_input;
    else if (move_check == 'Y') return(0); // returns 0 if ultimate ability used
    else {
        printf("False input, try again!\n");
        goto jump_get_input4;
    }
}