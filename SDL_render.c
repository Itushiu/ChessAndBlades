#include "functions.h"
#include "general_structures.h"

extern SDL_Window *window;
extern SDL_Surface *surface;

int SDL_render (piece_t board [8][8]) {

   SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));

    if (SDL_init_board() != 0) {
        return 1;
    }

    SDL_pieces(board);

    if (SDL_init_text() != 0) {
        return 1;
    }

    SDL_UpdateWindowSurface(window);

    return 0;
}