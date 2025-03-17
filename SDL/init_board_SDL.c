#include <SDL.h>
#include <SDL_error.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdbool.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//gcc whole_code_sdl.c -o chess $(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf

enum screen_size {
    SCREEN_WIDTH = 1000,
    SCREEN_HEIGHT = 800,
};

SDL_Window *window;
SDL_Surface *surface;

int board_sdl(void) {

    // Initialisierung von SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Initialisierung fehlgeschlagen! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Erstellt ein Fenster
    window = SDL_CreateWindow("Schach", SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Log("Fenster nicht erstellt! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    //Struktur um in SDL Pixelmanipulationen durchzuführen
    surface = SDL_GetWindowSurface(window);
    if (surface == NULL) {
        SDL_Log("Oberfläche nicht erhalten! SDL_Error: %s\n", SDL_GetError());
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