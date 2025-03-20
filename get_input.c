#include "functions.h"
#include "general_structures.h"

extern text_box_t text_box;
extern char text_box_buffer[500];
extern char prompt_buffer[500];
extern char inputBuffer[10];


int input_check(int input_value) { // clears input buffer and checks for EOF. Returns 1 if correct input
    inputBuffer[0] = '\0'; // clear input buffer 
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
        snprintf(prompt_buffer, 500, "Player White input your move (E.g. A2 A4 or E1 UT for ultimate):");
        SDL_get_input(prompt_buffer);
    } else {
        snprintf(prompt_buffer, 500, "Player Black input your move (E.g. A2 A4 or E1 UT for ultimate):");
        SDL_get_input(prompt_buffer);
    }

    input_value = sscanf(inputBuffer, " %c%c %c%c", &from_c, &from_r, &to_c, &to_r); // get 4 characters from input
    if (!input_check(input_value)) goto jump_get_input; // check for EOF, clear input buffer

    // check if ultimate skill
    if (('A' <= from_c && from_c <= 'H') && ('1' <= from_r && from_r <= '8') && to_c == 'U' && to_r == 'T') {
        ultimate = 1;
    }
    // check if valid input
    else if ((from_c < 'A' || from_c > 'H') || (from_r < '1' || from_r > '8') || (to_c < 'A' || to_c > 'H') || (to_r < '1' || to_r > '8')) {
        snprintf(text_box_buffer, 500, "%c: False input, try again!", current_player);
        text_box_add(&text_box, text_box_buffer);
        goto jump_get_input;
    }

    // turn these characters to int and fill the move array with them
    move[0] = from_c-'A'; // ascii leters A-H to 0-7 integers
    move[1] = from_r-'1'; // ascii numbers 1-8 to 0-7 integers
    move[2] = to_c-'A';
    move[3] = to_r-'1';

    // check if not empty figure
    if (board[move[0]][move[1]].type == ' ') {
        snprintf(text_box_buffer, 500, "%c: You can't play empty space, try again!", current_player);
        text_box_add(&text_box, text_box_buffer);
        goto jump_get_input;
    }

    // check if your figure
    if (current_player != board[move[0]][move[1]].color) {
        snprintf(text_box_buffer, 500, "%c: Not your figure, try again!", current_player);
        text_box_add(&text_box, text_box_buffer);
        goto jump_get_input;
    }

    if (ultimate == 1) goto jump_get_input_ultimate;

    // check if you actually move
    if (move[0] == move[2] && move[1] == move[3]) {
        snprintf(text_box_buffer, 500, "%c: You can't move to the same place, try again!", current_player);
        text_box_add(&text_box, text_box_buffer);
        goto jump_get_input;
    }

	if (board[move[2]][move[3]].type != ' ' && board[move[2]][move[3]].color == board[move[0]][move[1]].color) { // check if tried to attack your team
        snprintf(text_box_buffer, 500, "%c: Don't eat your team! Try again!", current_player);
        text_box_add(&text_box, text_box_buffer);
        goto jump_get_input;
    }

    if (board[move[2]][move[3]].type == ' ') { // move to empty space
    jump_get_input2:
        snprintf(prompt_buffer, 500, "You want to move your %c (HP: %d, ATT: %d, DEF: %d) to %c%c. Correct? (Y/N):", // show piece stats and check if sure
                board[move[0]][move[1]].type, board[move[0]][move[1]].hp, board[move[0]][move[1]].attack, board[move[0]][move[1]].defence, 
                to_c, to_r);
        SDL_get_input(prompt_buffer);
        
        input_value = sscanf(inputBuffer, " %c", &move_check);
        if (!input_check(input_value)) goto jump_get_input2; // check for EOF, clear input buffer
        if (move_check == 'N') goto jump_get_input;
        else if (move_check == 'Y') return(1); // returns 1 if normal move made
        else {
            snprintf(text_box_buffer, 500, "%c: False input, try again!", current_player);
            text_box_add(&text_box, text_box_buffer);
            goto jump_get_input2;
        }
    }
    
    else { // attack another piece
    jump_get_input3:
        snprintf(prompt_buffer, 500, "You want to attack enemy %c (HP: %d, ATT: %d, DEF: %d) with your %c (HP: %d, ATT: %d, DEF: %d). Correct? (Y/N):", // show pieces stats and check if sure
            board[move[2]][move[3]].type, board[move[2]][move[3]].hp, board[move[2]][move[3]].attack, board[move[2]][move[3]].defence,
            board[move[0]][move[1]].type, board[move[0]][move[1]].hp, board[move[0]][move[1]].attack, board[move[0]][move[1]].defence);
        SDL_get_input(prompt_buffer);    
        input_value = sscanf(inputBuffer, " %c", &move_check);
        if (!input_check(input_value)) goto jump_get_input3; // check for EOF, clear input buffer
        if (move_check == 'N') goto jump_get_input;
        else if (move_check == 'Y') return(1); // returns 1 if normal move made
        else {
            snprintf(text_box_buffer, 500, "%c: False input, try again!", current_player);
            text_box_add(&text_box, text_box_buffer);
            goto jump_get_input3;
        }
    }

jump_get_input_ultimate: // following for ultimate check

    if (board[move[0]][move[1]].ultimate == 0) {
        snprintf(text_box_buffer, 500, "%c: You already used the ultimate ability for this piece! Try again!", current_player);
        text_box_add(&text_box, text_box_buffer);
        goto jump_get_input;
    }

    switch (board[move[0]][move[1]].type) { // write the ultimate description for current piece for later use
        case 'P':
            ultimate_description = "Pawn Transform - Transform into any other piece after reaching end of the board (standard promotion)";
            break;
        case 'Q':
            ultimate_description = "Double Attack - Attack two pieces in a single turn (separate rolls)";
            break;
        case 'K':
            ultimate_description = "King Escape - Teleport to a random free location";
            break;
        case 'B':
            ultimate_description = "Bishop as King - Move one turn with King's movement pattern (cannot be an attack)";
            break;
        case 'R':
            ultimate_description = "Rook the Shield - Redirect next opponent's attack to itself and block any other ultimate while active";
            break;
        case 'H':
            ultimate_description = "Double Jump - Make two jumps in one turn (first one can't be an attack)";
            break;
    }

jump_get_input4:
    snprintf(text_box_buffer, 500, "Ultimate Ability of %c is %s", board[move[0]][move[1]].type, ultimate_description);
    text_box_add(&text_box, text_box_buffer);
    snprintf(prompt_buffer, 500, "You want to use the ultimate ability of your %c (HP: %d, ATT: %d, DEF: %d). Correct? (Y/N):", // show piece stats and ultimate and check if sure
        board[move[0]][move[1]].type, board[move[0]][move[1]].hp, board[move[0]][move[1]].attack, board[move[0]][move[1]].defence);
    SDL_get_input(prompt_buffer);
    
    input_value = sscanf(inputBuffer, " %c", &move_check);
    if (!input_check(input_value)) goto jump_get_input4; // check for EOF, clear input buffer
    if (move_check == 'N') goto jump_get_input;
    else if (move_check == 'Y') return(0); // returns 0 if ultimate ability used
    else {
        snprintf(text_box_buffer, 500, "%c: False input, try again!", current_player);
        text_box_add(&text_box, text_box_buffer);
        goto jump_get_input4;
    }
}