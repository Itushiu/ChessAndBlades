#include "functions.h"
#include "general_structures.h"
#include <string.h>

#define MAX_INPUT_LENGTH 10

//the function prompts a eingabeaufforderung on the lower part of the game window, reads the keyboard input 
//and returns the input move as a string

extern SDL_Window *window;
extern SDL_Surface *surface;

int showPrompt(char *prompt);	//help function: bekommt prompt als string; prompt ist die nachricht an den spieler
	

char *SDL_get_input(char *prompt) {	//the global function
	
	//initializing sdl sub systems
	//sdl_video
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("SDL_video konnte nicht initialisiert werden! SDL_video Error: %s\n",
			TTF_GetError());
			return -1;;
	}
	//sdl_ttf
	if (TTF_Init() == -1) {
	SDL_Log("SDL_ttf konnte nicht initialisiert werden! SDL_ttf Error: %s\n",
			TTF_GetError());
			return -1;
	}
	//setze farbe für Schrift auf weiß
	SDL_Color white = {.r = 255, .g = 255, .b = 255, .a = 255};
	//font und schriftgröße initialisieren
	TTF_Font *font = TTF_OpenFont("Go_Mono.ttf", 28);
	if (font == NULL) {
		SDL_Log("Schriftart konnte nicht geladen werden! SDL_ttf Error: %s\n",
		TTF_GetError());
		return -1;
	}
	
	if (showPrompt(prompt) != 0) { //invoke help function
		SDL_Log("showPrompt() fehlgeschlagen.");
	}
	
	char inputBuffer[MAX_INPUT_LENGTH] = ""; //input buffer für den eingegebenen text
	
	//event loop
	int isRunning = 1;
	SDL_Event event;
	
	SDL_StartTextInput();
	
	while(isRunning) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_TEXTINPUT:	//text wird eingegeben
					if (strlen(text) + strlen(event.text.text) < MAX_TEXT_LENGTH - 1) {
                    strcat(text, event.text.text);
					}
				case SDL_KEYDOWN:	//Sonderfälle: Entertaste gedrückt oder Löschen mit Backspace
					if (event.key.keysym.sym == SDLK_RETURN) {
						isRunning = 0;
						break;
					} else {
						if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(inputBuffer) > 0) {
							inputBuffer[strlen(inputBuffer) -1] = '\0';
						} 
					}
				default:
					break;
			}
		}

        // *nach jedem event neu rendern und änderungen an eingabe anzeigen (außer nach event entertaste)
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, inputBuffer, white);
        //converts the textSurface Surface object to the appropriate size for the window surface
		SDL_Surface *textSurface_converted = SDL_ConvertSurfaceFormat(inputBuffer, surface->format->format, 0);
		if (text_konvertiert == NULL) {
			SDL_Log("Text konnte nicht konvertiert werden! SDL_Error Error: %s\n",
            SDL_GetError());
			return -1;
		}
		
        SDL_Rect inputRect = {	//rect for input box
			.x = 10, 
			.y = 780, 
			.w = textSurface->w, 
			.h = textSurface->h
		};
		
		//copies the converted textSurface object inside the inputRect, and on to the global surface
		if (SDL_BlitSurface(textSurface_converted, NULL, surface, inputRect) != 0) {
			SDL_Log("Text konnte nicht kopiert werden! SDL_Error Error: %s\n",
            SDL_GetError());
			return -1;
		}

        SDL_FreeSurface(textSurface);
        SDL_FreeSurface(textSurface_converted);
        
        SDL_UpdateWindowSurface(window); // Änderungen anzeigen			
	}
	return inputBuffer;		//returns string
}


//showPrompt() zeigt über der input box eine eingabeaufforderung an, abhängig ob weiß oder schwarz am zug ist
int showPrompt(char *str) {
	//eingabeaufforderung für weiß
	if (current_player == 'w') {	
		SDL_Surface *prompt = TTF_RenderText_Solid(font, str, white);
		//text surface objekt wird konvertiert um an window surface angepasst zu sein
		//CHECK: make sure the surface object used here is the same as the surface object for our game window
		SDL_Surface *prompt_converted = SDL_ConvertSurfaceFormat(prompt, surface->format->format, 0);
		//fehlerbehandlung
		if (prompt_converted == NULL) {
			SDL_Log("Text konnte nicht konvertiert werden! SDL_Error Error: %s\n",
			SDL_GetError());
			return -1;
		}
	//eingabeaufforderung für schwarz
	} else {
		SDL_Surface *prompt = TTF_RenderText_Solid(font, str, white);
		//CHECK: make sure the surface object used here is the same as the surface object for our game window
		SDL_Surface *prompt_converted = SDL_ConvertSurfaceFormat(prompt, surface->format->format, 0);
		//fehlerbehandlung
		if (prompt_converted == NULL) {
			SDL_Log("Text konnte nicht konvertiert werden! SDL_Error Error: %s\n",
			SDL_GetError());
			return -1;
		}
	}
		
	//Zielrect für die eingabeaufforderung
	SDL_Rect promptRect = {	//soll unten hin
		.x = 10,
		.y = 770,
		.w = prompt_converted->w,
		.h = prompt_converted->h
	};
		
	//blitting the prompt at the correct location at the promptRect
	if (SDL_BlitSurface(prompt_converted, NULL, surface, &promptRect) != 0) {
		SDL_Log("Text konnte nicht kopiert werden! SDL_Error Error: %s\n", SDL_GetError());
		SDL_FreeSurface(text);
		SDL_FreeSurface(text_konvertiert);
		return -1;
	}
	SDL_FreeSurface(prompt);
	SDL_FreeSurface(prompt_converted);
	return 0;
}

int InitInput() {
	
