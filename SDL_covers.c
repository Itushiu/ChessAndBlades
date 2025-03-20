#include "functions.h"
#include "general_structures.h"
//gcc whole_code_sdl.c -o chess $(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf

//for sdl window
extern SDL_Window *window;
extern SDL_Surface *surface;
extern text_box_t text_box;

int SDL_covers(int posit_in_game) {
	// Initialisierung von SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("Initialization failed! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	// Erstellt ein Fenster
	if (window == NULL) window = SDL_CreateWindow("Chess & Blades", 10,
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
	
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 128, 128, 128));

	if (TTF_Init() == -1) {
		SDL_Log("SDL_ttf could not be initialized! SDL_ttf Error: %s\n", TTF_GetError());
		return -1;
	}

	TTF_Font *font = TTF_OpenFont("Go_Mono.ttf", 45);
	TTF_Font *small_font = TTF_OpenFont("Go_Mono.ttf", 30);

	if (font == NULL){
		SDL_Log("Font could not be loaded. SDL_ttf Error: %s\n", TTF_GetError());
		return -1;
	}
	
	// black color (SDL_Color)
	SDL_Color black_color = {.r = 0, .g = 0, .b = 0, .a = 255};
	SDL_Surface *text = NULL;
	SDL_Surface *small_text = NULL;
	//im callinf this function only twice with explicit values as parameter, no 3rd case is possible ?
	if (posit_in_game == 0) {
		// from text to pixels
		text = TTF_RenderText_Solid(font, "- RPG CHESS - ", black_color);
		small_text = TTF_RenderText_Solid(small_font, "ESC|leave & ENTER|start game", black_color);

		if (text == NULL || small_text == NULL) {
			SDL_Log("Text rendering failed: %s\n", TTF_GetError());
			TTF_CloseFont(font);
			return -1;
		}
	}
	else if (posit_in_game == 2){
		text = TTF_RenderText_Solid(font, "- GAME OVER - ", black_color);
		small_text = TTF_RenderText_Solid(small_font, text_box.text[text_box.count - 2], black_color);
		if (text == NULL || small_text == NULL) {
			SDL_Log("Text rendering failed: %s\n", TTF_GetError());
			TTF_CloseFont(font);
			return -1;
		}

	}
	else  {
		// from text to pixels
		text = TTF_RenderText_Solid(font, "- THE END - ", black_color);
		small_text = TTF_RenderText_Solid(font, "ESC|leave", black_color);
		
		if (text == NULL || small_text == NULL) {
			SDL_Log("Text rendering failed: %s\n", TTF_GetError());
			TTF_CloseFont(font);
			TTF_CloseFont(small_font);
			return -1;
		}
	}
	
	SDL_Surface *text_konvertiert = SDL_ConvertSurfaceFormat(text, surface->format->format, 0);
	SDL_Surface *small_text_konvertiert = SDL_ConvertSurfaceFormat(small_text, surface->format->format, 0);
	
	if (text_konvertiert == NULL ||small_text_konvertiert == NULL) {
		SDL_Log("Text konnte nicht konvertiert werden! SDL_Error Error: %s\n", SDL_GetError());
		SDL_FreeSurface(text);
		SDL_FreeSurface(small_text);
		TTF_CloseFont(font);
		TTF_CloseFont(small_font);
		return -1;
	}
	SDL_FreeSurface(text);
	SDL_FreeSurface(small_text);

	// Define a destination rectangle to center the text
	SDL_Rect text_rect;
	text_rect.x = (SCREEN_WIDTH - text_konvertiert->w) / 2;
	text_rect.y = (SCREEN_HEIGHT - text_konvertiert->h) / 2;
	text_rect.w = text_konvertiert->w;
	text_rect.h = text_konvertiert->h;

	SDL_Rect small_text_rect;
	small_text_rect.x = (SCREEN_WIDTH - small_text_konvertiert->w) / 2;
	small_text_rect.y = text_rect.y + text_rect.h + 10;
	small_text_rect.w = small_text_konvertiert->w;
	small_text_rect.h = small_text_konvertiert->h;


	SDL_BlitSurface(text_konvertiert, NULL, surface, &text_rect);
	SDL_BlitSurface(small_text_konvertiert, NULL, surface, &small_text_rect);
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
				if (event.key.keysym.sym == SDLK_RETURN && posit_in_game == 0) {
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
	TTF_CloseFont(small_font);
    TTF_Quit();
	if (decision != 0){
		exit(0);
	}
	return decision;
}
