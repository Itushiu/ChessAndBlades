#include "functions.h"
#include "general_structures.h"

extern text_box_t text_box;
extern char text_box_buffer[500];

int print_board(piece_t board[8][8]);		// print the current state of the board

int calculate_attack(piece_t board [8][8], int move[4]); // here is where the actual move is happening

int validate_move_k(int move[4], piece_t board[8][8]); // king rules needed for bishop ultimate

int input_check(int input_value); // needed for pawns



int ultimate_ability_r(int move[4], piece_t board [8][8], char *current_player) { // Rook Shield
    int shield_active = 1;
    board[move[0]][move[1]].ultimate = 0;
    int shield_position[2]; // save coordinates of rook that used the ultimate
    shield_position[0] = move[0];
    shield_position[1] = move[1]; 
    char shield_color = *current_player; // save color of shield

    snprintf(text_box_buffer, 500, "Next attack of your opponent will be redirected to your Rook.");
    text_box_add(&text_box, text_box_buffer);
    //print_board(board);
    *current_player = (*current_player == 'w') ? 'b' : 'w'; // switch 

    while (shield_active) { // game plays normal until rook redirected an attack
        if (get_input(move, board, *current_player)) {	// normal move from input
            if (validate_moves(board, move)) {	// knows the rules
                if (board[move[2]][move[3]].color == shield_color) {
                    move[2] = shield_position[0];
                    move[3] = shield_position[1];
                    shield_active = 0;
                }
                if(make_move(board, move) == 1){
                    return 0;
                }
                *current_player = (*current_player == 'w') ? 'b' : 'w'; // switch 
            }
            else {
                snprintf(text_box_buffer, 500, "Not a valid move for %c! Try again!", board[move[0]][move[1]].type);
                text_box_add(&text_box, text_box_buffer);
            }
        }
        else {
            snprintf(text_box_buffer, 500, "No ultimate ability can be used, because Rook the Shield is still active.");
            text_box_add(&text_box, text_box_buffer);
        }
    }
    return 1;
}


int ultimate_ability_q(int move[4], piece_t board [8][8], char *current_player) {
    int queen_position[2]; // save coordinates of queen that used the ultimate
    queen_position[0] = move[0];
    queen_position[1] = move[1];
    int first_move_king_attack = 0;
    int second_move_king_attack = 0;
    
    printf("\nPlease input your first attack.\n");
    if (!get_input(move, board, *current_player)) { // normal move from input
        snprintf(text_box_buffer, 500, "You can't use another ultimate ability while using this ultimate ability!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    	}
    if (move[0] != queen_position[0] || move[1] != queen_position[1]) { // checks if tried to attack with queen
        snprintf(text_box_buffer, 500, "You can't move another piece while using this ultimate ability!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }
    if (board[move[2]][move[3]].type == ' ') { // checks if tried to attack
        snprintf(text_box_buffer, 500, "Your Queen has to attack if you want to use her ultimate ability!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }
    if (!validate_moves(board, move)) {	// knows the rules
        snprintf(text_box_buffer, 500, "The move you tried to make is not valid!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }

    int first_move[4]; 
    for (int i = 0; i < 4; i++) first_move[i] = move[i]; // save first move
 
    printf("\nPlease input your second attack.\n");
    if (!get_input(move, board, *current_player)) { // normal move from input
        snprintf(text_box_buffer, 500, "You can't use another ultimate ability while using this ultimate ability!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    	}
    if (move[0] != queen_position[0] || move[1] != queen_position[1]) { // checks if tried to attack with queen
        snprintf(text_box_buffer, 500, "You can't move another piece while using this ultimate ability!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }
    if (board[move[2]][move[3]].type == ' ') { // checks if tried to attack
        snprintf(text_box_buffer, 500, "Your Queen has to attack if you want to use her ultimate ability!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }
    if (!validate_moves(board, move)) {	// knows the rules
        snprintf(text_box_buffer, 500, "The move you tried to make is not valid!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }

    if (move[2] == first_move[2] && move[3] == first_move[3]) { // checks if tried to attack the same piece
        snprintf(text_box_buffer, 500, "You can't attack the same piece twice!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }
    
    board[queen_position[0]][queen_position[1]].ultimate = 0; // ultimate used

    if (board[first_move[2]][first_move[3]].type == 'K') first_move_king_attack = 1; // check if first move attacked king
    if (board[move[2]][move[3]].type == 'K') second_move_king_attack = 1; // check if second move attacked king

	int move_result = calculate_attack(board, first_move); // returns 1 if my enemy died, 2 if my figure died, 0 otherwise 
    if (move_result == 1) { // if enemy piece died
        if (first_move_king_attack == 1) return 0; // end if enemy king died
        board[first_move[0]][first_move[1]] = board[first_move[2]][first_move[3]]; // move queen back
        board[first_move[2]][first_move[3]].type = ' ';
        board[first_move[2]][first_move[3]].color = ' ';
        board[first_move[2]][first_move[3]].hp = ' ';
        board[first_move[2]][first_move[3]].attack = ' ';
        board[first_move[2]][first_move[3]].defence = ' ';
        board[first_move[2]][first_move[3]].ultimate = 0;

    }
    else if (move_result == 2) return 1;
    
	move_result = calculate_attack(board, move); // returns 1 if my enemy died, 2 if my figure died, 0 otherwise 
    if (move_result == 1) { // if enemy piece died
        if (second_move_king_attack == 1) return 0; // end if enemy king died
    }
    else if (move_result == 2) return 1;

    return 1;
}


int ultimate_ability_k(int move[4], piece_t board [8][8], char *current_player) {
    board[move[0]][move[1]].ultimate = 0; // ultimate used
    int random_column, random_row;
    while (1) {
        random_column = rand() % (7 + 1 - 0) + 0; // rand() % (max_number + 1 - minimum_number) + minimum_number
        random_row = rand() % (7 + 1 - 0) + 0; // rand() % (max_number + 1 - minimum_number) + minimum_number
        if (board[random_column][random_row].type == ' ') break; // if found empty random tile
    }
   
    board[random_column][random_row] = board[move[0]][move[1]]; // move king
    board[move[0]][move[1]].type = ' ';
    board[move[0]][move[1]].color = ' ';
    board[move[0]][move[1]].hp = ' ';
    board[move[0]][move[1]].attack = ' ';
    board[move[0]][move[1]].defence = ' ';
    board[move[0]][move[1]].ultimate = 0;

    snprintf(text_box_buffer, 500, "Your king escaped to %c%c!", random_column+'A', random_row+'1');
    text_box_add(&text_box, text_box_buffer);
    
    return 1;
}


int ultimate_ability_h(int move[4], piece_t board [8][8], char *current_player) {
    piece_t board_copy[8][8]; // create a copy of board
    for (int i= 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) board_copy[i][j] = board[i][j];
    }

    int knight_position[2]; // save coordinates of queen that used the ultimate
    knight_position[0] = move[0];
    knight_position[1] = move[1];
    
    printf("\nPlease input your first move.\n");
    if (!get_input(move, board_copy, *current_player)) { // normal move from input
        snprintf(text_box_buffer, 500, "You can't use another ultimate ability while using this ultimate ability!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    	}
    if (move[0] != knight_position[0] || move[1] != knight_position[1]) { // checks if tried to move knight
        snprintf(text_box_buffer, 500, "You can't move another piece while using this ultimate ability!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }
    if (board_copy[move[2]][move[3]].type != ' ') { // checks if tried to attack
        snprintf(text_box_buffer, 500, "You can't attack another piece on the first move of this ultimate ability!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }
    if (!validate_moves(board_copy, move)) {	// knows the rules
        snprintf(text_box_buffer, 500, "The move you tried to make is not valid!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }

    make_move(board_copy, move);

    knight_position[0] = move[2];
    knight_position[1] = move[3];
    
    printf("Please input your second move.\n");
    if (!get_input(move, board_copy, *current_player)) { // normal move from input
        snprintf(text_box_buffer, 500, "You can't use another ultimate ability while using this ultimate ability!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    	}
    if (move[0] != knight_position[0] || move[1] != knight_position[1]) { // checks if tried to move knight
        snprintf(text_box_buffer, 500, "You can't move another piece while using this ultimate ability!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }
    if (!validate_moves(board_copy, move)) {	// knows the rules
        snprintf(text_box_buffer, 500, "The move you tried to make is not valid!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }

    
    board_copy[knight_position[0]][knight_position[1]].ultimate = 0; // ultimate used

    // change the main board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) board[i][j] = board_copy[i][j];
    } 

    if(make_move(board, move) == 1){
        return 0;
    }
    

    return 1;
}


int ultimate_ability_b(int move[4], piece_t board [8][8], char *current_player) {
    int bishop_position[2]; // save coordinates of queen that used the ultimate
    bishop_position[0] = move[0];
    bishop_position[1] = move[1];

    printf("\nPlease input the move of your Bishop.\n");
    if (!get_input(move, board, *current_player)) { // normal move from input
        snprintf(text_box_buffer, 500, "You can't use another ultimate ability while using this ultimate ability!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    	}
    if (move[0] != bishop_position[0] || move[1] != bishop_position[1]) { // checks if tried to move the bishop
        snprintf(text_box_buffer, 500, "You can't move another piece while using this ultimate ability!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }
    if (board[move[2]][move[3]].type != ' ') { // checks if tried to attack
        snprintf(text_box_buffer, 500, "Your Bishop can't attack if you want to use its ultimate ability!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }
    if (!validate_move_k(move, board)) {	// knows the rules
        snprintf(text_box_buffer, 500, "The move you tried to make is not valid!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }

    make_move(board, move);   

    board[move[2]][move[3]].ultimate = 0; // ultimate used

    return 1;
}


int ultimate_ability_p(int move[4], piece_t board [8][8], char *current_player) {
    if ((move[1] != 0 && *current_player == 'b') || (move[1] != 7 && *current_player == 'w')) { // check if pawn is in the first row
        snprintf(text_box_buffer, 500, "Your pawn is in the wrong row to use its ultimate ability!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }
    char pawn_transform_type;

    while (1) { // get piece type input
        printf("\nInput the piece you want your pawn to transform into (E.g. B for Bishop): ");
        int input_value = scanf(" %c", &pawn_transform_type);
        if (!input_check(input_value)) continue; // check for EOF, clear input buffer (function from get_input.c)
        else if (pawn_transform_type == 'B' || pawn_transform_type == 'R' || pawn_transform_type == 'H' || pawn_transform_type == 'Q') break; // checks if type == one of possible pieces
        else {
            snprintf(text_box_buffer, 500, "False input, try again!");
            text_box_add(&text_box, text_box_buffer);
            continue;
        }
    }

    int already_exist = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (pawn_transform_type == board[i][j].type && board[i][j].color == *current_player) already_exist++; // count the number of existing pieces with this type
        }
    } 

    if (already_exist > 1 || (already_exist > 0 && pawn_transform_type == 'Q')) { // checks this type is not "full"
        snprintf(text_box_buffer, 500, "You already have max number of this piece!");
        text_box_add(&text_box, text_box_buffer);
        return 2;
    }

    board[move[0]][move[1]].type = pawn_transform_type;
    return 1;
}



int ultimate_abilities(int move[4], piece_t board [8][8], char *current_player) {

    int ultimate_result; // used as a return from diefferent ultimate_moves

    switch (board[move[0]][move[1]].type) {		//goes to appropriate function depending on the type of the piece
        case 'R':
            ultimate_result = ultimate_ability_r(move, board, current_player);
            if (ultimate_result == 1) { // returns 1 if all good, 0 if king died (game end)
                return 1;
            } else {
                return 0;
            }
        case 'Q':
            ultimate_result = ultimate_ability_q(move, board, current_player);
            if (ultimate_result == 1) { // returns 1 if all good, 0 if king died (game end), 2 if incorrectly used
                //print_board(board);
                SDL_render(board);
                *current_player = (*current_player == 'w') ? 'b' : 'w'; // switch 
                return 1;
            } else if (ultimate_result == 2) {
                //print_board(board);
                SDL_render(board);
                snprintf(text_box_buffer, 500, "You used the ultimate ability of your Queen incorrectly! Repeat your move from the start.");
                text_box_add(&text_box, text_box_buffer);
                return 2;
            }
            else  {
                //print_board(board);
                SDL_render(board);
                snprintf(text_box_buffer, 500, "GAME OVER, PLAYER %c WINS!", *current_player);
                text_box_add(&text_box, text_box_buffer);
                return 0;
            }
        case 'K':
            srand(time(NULL)); // random seed from current time
            ultimate_result = ultimate_ability_k(move, board, current_player);
            if (ultimate_result == 1) {
                //print_board(board);
                SDL_render(board);
                *current_player = (*current_player == 'w') ? 'b' : 'w'; // switch 
                return 1;
            } else { // shouldn't happen
                return 2;
            }
        case 'H':
            ultimate_result = ultimate_ability_h(move, board, current_player);
            if (ultimate_result == 1) {
                *current_player = (*current_player == 'w') ? 'b' : 'w'; // switch 
                return 1;
            } else if (ultimate_result == 2) {
                //print_board(board);
                SDL_render(board);
                snprintf(text_box_buffer, 500, "You used the ultimate ability of your Knight incorrectly! Repeat your move from the start.");
                text_box_add(&text_box, text_box_buffer);
                return 2;            
            } else {
                return 0;
            }
        case 'B':
            ultimate_result = ultimate_ability_b(move, board, current_player);
            if (ultimate_result == 1) {
                *current_player = (*current_player == 'w') ? 'b' : 'w'; // switch 
                return 1;
            } else {
                //print_board(board);
                SDL_render(board);
                snprintf(text_box_buffer, 500, "You used the ultimate ability of your Bishop incorrectly! Repeat your move from the start.");
                text_box_add(&text_box, text_box_buffer);
                return 2;
            }
        case 'P':
            ultimate_result = ultimate_ability_p(move, board, current_player);
            if (ultimate_result == 1) {
                //print_board(board);
                SDL_render(board);
                *current_player = (*current_player == 'w') ? 'b' : 'w'; // switch 
                return 1;
            } else {
                //print_board(board);
                SDL_render(board);
                snprintf(text_box_buffer, 500, "You used the ultimate ability of your Pawn incorrectly! Repeat your move from the start.");
                text_box_add(&text_box, text_box_buffer);
                return 2;
            }
        case ' ':
            return 2;
    }
    return 2;
}
