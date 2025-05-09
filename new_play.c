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

char inputBuffer[10] = ""; //buffer for sdl input
char prompt_buffer[500]; // used to put individual strings inside of prompt

char current_player = 'w';

extern SDL_Window *window;
extern SDL_Surface *surface;
int main(void) {

    int posit_in_game = 0;
    if (SDL_covers(posit_in_game) != 0) {
        goto end_of_file;
    }
    if (SDL_rules(posit_in_game) != 0) {
        goto end_of_file;
    }
    text_box.count = 0; // set initial count for text_box

    init_chessboard(board);

    if (SDL_render(board) != 0) { // initial render of the board, checks for errors
        goto end_of_file;
    }

    int move[4];

   bool quit = false;  //not sure, works, have to check, gpt suggestion for error i gave him (till line 41)
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
				//escape to exit
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
					break;
				}
			}
        }
         if (quit) {
            break;
        }

        // here have to change to new get input
        if (get_input(move, board, current_player)) { // returns 1 for a normal move
            if (validate_moves(board, move)) {
                if (make_move(board, move) == 1){
                    posit_in_game = 2;
                    break; 
                }
                   
                current_player = (current_player == 'w') ? 'b' : 'w';
            } else {
                snprintf(text_box_buffer, 500, "%c: Not a valid move for %c! Try again!", current_player, board[move[0]][move[1]].type);
                text_box_add(&text_box, text_box_buffer);
            }
        }
        else { //ultimate (get_input returns 0)
            if (ultimate_abilities(move, board, &current_player) == 0){
                posit_in_game = 2;
                break;
            }
        }
    }
    //helped once, here not so sure
    SDL_Delay(5000);
    if (posit_in_game == 2){
        if (SDL_covers(posit_in_game) != 0) {
        goto end_of_file;
        }
    }
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
