#include <SDL.h>
#include <SDL_error.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdbool.h>
#include <SDL_image.h>

//Kompilieren gcc schach.c -o schach $(sdl2-config --cflags --libs) -lSDL2_image


enum screen_size {
    SCREEN_WIDTH = 1000,
    SCREEN_HEIGHT = 720,
};

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) { // Initialisierung von SDL
        SDL_Log("Initialisierung fehlgeschlagen! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Schach", SDL_WINDOWPOS_UNDEFINED, // Erstellt ein Fenster
                                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Log("Fenster nicht erstellt! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    SDL_Surface *surface = SDL_GetWindowSurface(window); //Struktur um in SDL Pixelmanipulationen durchzuführen
    if (surface == NULL) {
        SDL_Log("Oberfläche nicht erhalten! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Farben erstellen
    Sint32 white = SDL_MapRGBA(surface->format, 255, 255, 255, 255);
    Sint32 grey = SDL_MapRGBA(surface->format, 128, 128, 128, 255);

    //Größe der Rechtecke
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