#include <SDL.h>
#include <SDL_error.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdbool.h>

enum screen_size {
    SCREEN_WIDTH = 1000,
    SCREEN_HEIGHT = 640,
};

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Initialisierung fehlgeschlagen! SDL_Error: %s\n", SDL_GetError());
    return -1;
    }
    SDL_Window *window = SDL_CreateWindow("Schach", SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Surface *surface = SDL_GetWindowSurface(window); //Struktur um in SDL Pixelmanipulationen durchzuführen

    Sint32 white = SDL_MapRGBA(surface->format, 255, 255, 255, 255);
    Sint32 grey = SDL_MapRGBA(surface->format, 128, 128, 128, 255);

    int rect_size = 80;

    for(int row = 0; row <8; row++) {
        for(int column = 0; column < 8; column++) {
            SDL_Rect rect = {
                .x = column * rect_size, // x stellt die horizontale Position dar
                .y = row * rect_size, // y stellt die vertikale Position dar
                .w = rect_size, // w stellt die Breite des Rechtecks dar
                .h = rect_size, // h stellt die Höhe des Rechtecks dar
            };

            if ((row + column) % 2 == 0) {
                SDL_FillRect(surface, &rect, white);
            } else {
                SDL_FillRect(surface, &rect, grey);
            }
        }
    }
    
    


    SDL_UpdateWindowSurface(window);

    SDL_Event e;
    bool quit = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
        }
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}