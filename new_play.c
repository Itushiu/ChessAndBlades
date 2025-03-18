#include "functions.h"
#include "general_structures.h"

extern SDL_Window *window;
extern SDL_Surface *surface;
int main(void) {

    extern piece_t board[8][8];
    init_chessboard(board);

    //from sdl
    int ausgabe = SDL_init_board();
    if (ausgabe != 0) {
        goto end_of_file;
	}
    ausgabe = SDL_init_chess_figures();
    if (ausgabe != 0) {
        goto end_of_file;
    }

    ausgabe = SDL_init_text();
    if (ausgabe != 0) {
        goto end_of_file;
    }

    SDL_UpdateWindowSurface(window);

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
                //next line added via gpt because of glitches on the screen, it colors everything black
                SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
                SDL_init_board();
                SDL_init_text();
                SDL_pieces(board);
                //init_text_sdl();
                SDL_UpdateWindowSurface(window);
                current_player = (current_player == 'w') ? 'b' : 'w';
            } else {
                printf("Not a valid move for %c! Try again!\n", board[move[0]][move[1]].type);
            }
        }
        else { //ultimate (get_input returns 0)
            if (ultimate_abilities(move, board, &current_player) == 0)
                break;

            // Refresh SDL display after ultimate move.
            SDL_init_board();
            SDL_pieces(board);
            SDL_init_text();
            SDL_UpdateWindowSurface(window);
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