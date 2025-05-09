#include "functions.h"
#include "general_structures.h"
//gcc whole_code_sdl.c -o chess $(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf

//for sdl window
SDL_Window *window;
SDL_Surface *surface;

int SDL_init_board(void) {

    // Initialisierung von SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Initialization failed! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Erstellt ein Fenster
    if (window == NULL) window = SDL_CreateWindow("Schach", 10,
                                            10, SCREEN_WIDTH,
                                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Log("Window not created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    //Struktur um in SDL Pixelmanipulationen durchzuführen
    surface = SDL_GetWindowSurface(window);
    if (surface == NULL) {
        SDL_Log("Surface not preserved! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Farben erstellen (int)
    Sint32 white = SDL_MapRGBA(surface->format, 255, 255, 255, 255);
    Sint32 grey = SDL_MapRGBA(surface->format, 128, 128, 128, 255);
    
    int rect_size = 90;

    //Schachbrett erstellen
    for(int row = 0; row <8; row++) {
        for(int column = 0; column < 8; column++) {
            SDL_Rect rect = {
                .x = column * rect_size, // x stellt die horizontale Position dar
                .y = row * rect_size, // y stellt die vertikale Position dar
                .w = rect_size, // w stellt die Breite des Rechtecks dar
                .h = rect_size, // h stellt die Höhe des Rechtecks dar
            };

            //Farbe des Rechtecks
            if ((row + column) % 2 == 0) {
                SDL_FillRect(surface, &rect, white);
            } else {
                SDL_FillRect(surface, &rect, grey);
            }
        }
    }
    return 0;
}