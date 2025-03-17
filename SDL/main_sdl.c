#include <SDL.h>
#include <SDL_error.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdbool.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//Kompilieren: gcc -o chess_sdl main_sdl.c init_board_SDL.c init_chess_figures.c init_text_sdl.c $(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf

// Globale Variablen das in allen Dateien gleiche größe ist
extern SDL_Window *window;
extern SDL_Surface *surface;

// Funktionsprototypen für die anderen Dateien
int board_sdl(void);
int chess_figures_sdl(void);
int text_sdl(void);

int main(void) {
    
    // Initialisierung des Bretts
    int ausgabe = board_sdl();
    if (ausgabe != 0) {
        goto end_of_file;
    }
    
    // Figuren laden und platzieren
    ausgabe = chess_figures_sdl();
    if (ausgabe != 0) {
        goto end_of_file;
    }
    
    // Text und Beschriftungen hinzufügen
    ausgabe = text_sdl();
    if (ausgabe != 0) {
        goto end_of_file;
    }
    
    // Aktualisiere das Fenster
    SDL_UpdateWindowSurface(window);
    
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

end_of_file:
    TTF_Quit();
    IMG_Quit();
    if (window != NULL) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    return ausgabe;
}