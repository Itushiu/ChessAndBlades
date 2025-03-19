#include "functions.h"
#include "general_structures.h"

//backend row/colums
int row;
int column;

//where we store pieces
piece_t board[8][8];

// where we store text logs
text_box_t text_box;
char text_box_buffer[500]; // used to put individual strings inside of text_box

extern SDL_Window *window;
extern SDL_Surface *surface;
int main(void) {

    int posit_in_game = 0;
    if (SDL_covers(posit_in_game) != 0) {
        goto end_of_file;
    }
    text_box.count = 0; // set initial count for text_box

    init_chessboard(board);

    if (SDL_init_chess_figures() != 0 || SDL_render(board) != 0) { // initial render of the board, checks for errors
        goto end_of_file;
    }

    int move[4];
    char current_player = 'w';

   bool quit = false;  //not sure, works, have to check, gpt suggestion for error i gave him (till line 41)
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        if (quit) {
            break;
        }

        // here have to change to new get input
        if (get_input(move, board, current_player)) { // returns 1 for a normal move
            if (validate_moves(board, move)) {
                if (make_move(board, move) == 1)
                    break; 
                current_player = (current_player == 'w') ? 'b' : 'w';
            } else {
                snprintf(text_box_buffer, 500, "Not a valid move for %c! Try again!", board[move[0]][move[1]].type);
                text_box_add(&text_box, text_box_buffer);
            }
        }
        else { //ultimate (get_input returns 0)
            if (ultimate_abilities(move, board, &current_player) == 0)
                break;
        }
    }
    //helped once, here not so sure
    SDL_Delay(10000);
    posit_in_game = 1;
    if (SDL_covers(posit_in_game) != 0) {
        goto end_of_file;
    }
	end_of_file:
    	TTF_Quit();
    	IMG_Quit();
    	if (window != NULL) {
        	SDL_DestroyWindow(window);
    	}
    	SDL_Quit();
    return 0;
}