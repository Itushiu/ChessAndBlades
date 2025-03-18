#include "functions.h"
#include "general_structures.h"
//gcc whole_code_sdl.c -o chess $(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf

//for sdl window
enum screen_size {
    SCREEN_WIDTH = 1400,
    SCREEN_HEIGHT = 790,
};
extern SDL_Window *window;
extern SDL_Surface *surface;

int SDL_covers(int posit_in_game) {
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
	
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 128, 128, 128));

	if (TTF_Init() == -1) {
		SDL_Log("SDL_ttf could not be initialized! SDL_ttf Error: %s\n", TTF_GetError());
		return -1;
	}

	TTF_Font *font = TTF_OpenFont("Go_Mono.ttf", 45);
	if (font == NULL){
		SDL_Log("Font could not be loaded. SDL_ttf Error: %s\n", TTF_GetError());
		return -1;
	}
	
	// white color (SDL_Color)
	SDL_Color black_color = {.r = 0, .g = 0, .b = 0, .a = 255};
	SDL_Surface *text = NULL;
	//im callinf this function only twice with explicit values as parameter, no 3rd case is possible ?
	if (posit_in_game == 0) {
		// from text to pixels
		text = TTF_RenderText_Solid(font, "- RPG CHESS - ", black_color);
		if (text == NULL) {
			SDL_Log("Text rendering failed: %s\n", TTF_GetError());
			TTF_CloseFont(font);
			return -1;
		}
	}
	else {
		// from text to pixels
		text = TTF_RenderText_Solid(font, "- THE END - ", black_color);
		if (text == NULL) {
			SDL_Log("Text rendering failed: %s\n", TTF_GetError());
			TTF_CloseFont(font);
			return -1;
		}
	}
	
	SDL_Surface *text_konvertiert = SDL_ConvertSurfaceFormat(text, surface->format->format, 0);
	if (text_konvertiert == NULL) {
		SDL_Log("Text could not be converted! SDL_Error Error: %s\n", SDL_GetError());
		SDL_FreeSurface(text);
		TTF_CloseFont(font);
		return -1;
	}
	SDL_FreeSurface(text);

	// Define a destination rectangle to center the text
	SDL_Rect text_rect;
	text_rect.x = (SCREEN_WIDTH - text_konvertiert->w) / 2;
	text_rect.y = (SCREEN_HEIGHT - text_konvertiert->h) / 2;
	text_rect.w = text_konvertiert->w;
	text_rect.h = text_konvertiert->h;

	SDL_BlitSurface(text_konvertiert, NULL, surface, &text_rect);
	SDL_UpdateWindowSurface(window);
	SDL_UpdateWindowSurface(window);

	SDL_Event event;
	int decision = -1;
	while (1) {
		if (SDL_WaitEvent(&event)) {
			if (event.type == SDL_QUIT) {
				decision = -1;
				break;
			}
			else if (event.type == SDL_KEYDOWN) {
				//enter for the game
				if (event.key.keysym.sym == SDLK_RETURN) {
					decision = 0;
					break;
				}
				//escape to exit
				else if (event.key.keysym.sym == SDLK_ESCAPE) {
					decision = -1;
					break;
				}
			}
		}
	}
	SDL_FreeSurface(text_konvertiert);
    TTF_CloseFont(font);
    TTF_Quit();
	return decision;
}
