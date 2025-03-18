#include "functions.h"
#include "general_structures.h"

//backend row/colums
int row;
int column;

//where we store pieces
piece_t board[8][8];

extern SDL_Window *window;
extern SDL_Surface *surface;
int main(void) {

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
                printf("Not a valid move for %c! Try again!\n", board[move[0]][move[1]].type);
            }
        }
        else { //ultimate (get_input returns 0)
            if (ultimate_abilities(move, board, &current_player) == 0)
                break;
        }
    }
    //helped once, here not so sure
    SDL_Delay(2000);
	end_of_file:
    	TTF_Quit();
    	IMG_Quit();
    	if (window != NULL) {
        	SDL_DestroyWindow(window);
    	}
    	SDL_Quit();
    return 0;
}