#include "functions.h"
#include "general_structures.h"
#include <string.h>



//the function prompts a eingabeaufforderung on the lower part of the game window, reads the keyboard input 
//and returns the input move as a string

//extern SDL_Window *window;
//extern SDL_Surface *surface;

int showPrompt(char *prompt);	//help function: bekommt prompt als string; prompt ist die nachricht an den spieler
	

int SDL_get_input(char *prompt) {	//the global function
	
	extern SDL_Window *window;
	extern SDL_Surface *surface;
	
	extern char inputBuffer[10];
	
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
	
	//char inputBuffer[10] = ""; //input buffer für den eingegebenen text
	
	//event loop
	int isRunning = 1;
	SDL_Event event;
	
	SDL_StartTextInput();
	
	while(isRunning) {
		while (SDL_PollEvent(&event)) {	//will be entered each time until there are no more events in the queue
			switch (event.type) {
				case SDL_TEXTINPUT:	//text wird eingegeben
					if (strlen(inputBuffer) + strlen(event.text.text) < 10 - 1) {
                    strcat(inputBuffer, event.text.text);
                    break;
					}
				case SDL_KEYDOWN:	//Sonderfälle: Entertaste gedrückt oder Löschen mit Backspace
					if (event.key.keysym.sym == SDLK_RETURN) {
						isRunning = 0;	//highest while loop should not be entered again
						break;
					} else if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(inputBuffer) > 0) {
							inputBuffer[strlen(inputBuffer) -1] = '\0';
							break;
					} else if (even.key.keysym.sym == SDLK_ESCAPE) {
					}
				default:
					break;
			}
			break; //leave the while loop that fetches new events from the queue in order to render updated input text
		}

		
        // *nach jedem event neu rendern und änderungen an eingabe anzeigen (außer nach event entertaste)
        SDL_Surface *textSurface = NULL;
        if (strlen(inputBuffer) > 0) {
			textSurface = TTF_RenderText_Solid(font, inputBuffer, white);
		} else {
			textSurface = TTF_RenderText_Solid(font, " ", white);
		}

        //converts the textSurface Surface object to the appropriate size for the window surface
		SDL_Surface *textSurface_converted = SDL_ConvertSurfaceFormat(textSurface, surface->format->format, 0);
		if (textSurface_converted == NULL) {
			SDL_Log("Text konnte nicht konvertiert werden! SDL_Error Error: %s\n",
            SDL_GetError());
			return -1;
		}
		
		
        SDL_Rect inputRect = {	//rect for input box
			.x = (strlen(prompt) * 18 + 10), 
			.y = 770, 
			.w = 300, 
			.h = textSurface->h
		};
		SDL_FillRect(surface, &inputRect, SDL_MapRGB(surface->format, 0, 0, 0)); //färbt inputRect schwarz
		
		//copies the converted textSurface object inside the inputRect, and on to the global surface
		if (SDL_BlitSurface(textSurface_converted, NULL, surface, &inputRect) != 0) {
			SDL_Log("Text konnte nicht kopiert werden! SDL_Error Error: %s\n",
            SDL_GetError());
			return -1;
		}

        SDL_FreeSurface(textSurface);
        SDL_FreeSurface(textSurface_converted);
        
        SDL_UpdateWindowSurface(window); // Änderungen anzeigen			
	}
	SDL_StopTextInput();
	//check correctness of Buffer!!!!
	return 0;		
}


//showPrompt() zeigt über der input box eine eingabeaufforderung an, die der funktion als argument übergeben wird (prompt)
int showPrompt(char *prompt) {
	
	extern SDL_Window *window;
	extern SDL_Surface *surface;
	
	//setze farbe für Schrift auf weiß
	SDL_Color white = {.r = 255, .g = 255, .b = 255, .a = 255};
	//font und schriftgröße initialisieren
	TTF_Font *font = TTF_OpenFont("Go_Mono.ttf", 28);
	if (font == NULL) {
		SDL_Log("Schriftart konnte nicht geladen werden! SDL_ttf Error: %s\n",
		TTF_GetError());
		return -1;
	}
	
	SDL_Surface *promptSurface = TTF_RenderText_Solid(font, prompt, white);
	if (promptSurface == NULL) {
		SDL_Log("Text rendering failed. %s\n", TTF_GetError());
		return -1;
	}
	//text surface objekt wird konvertiert um an window surface angepasst zu sein
	//CHECK: make sure the surface object used here is the same as the surface object for our game window
	SDL_Surface *promptSurface_converted = SDL_ConvertSurfaceFormat(promptSurface, surface->format->format, 0);
	//fehlerbehandlung
	if (promptSurface_converted == NULL) {
		SDL_Log("Text konnte nicht konvertiert werden! SDL_Error Error: %s\n",
		SDL_GetError());
		return -1;
	}
	
	//Zielrect für die eingabeaufforderung
	SDL_Rect promptRect = {	//soll unten hin
		.x = 10,
		.y = 770,
		.w = promptSurface_converted->w,
		.h = promptSurface_converted->h
	};
		
	//blitting the prompt at the correct location at the promptRect
	if (SDL_BlitSurface(promptSurface_converted, NULL, surface, &promptRect) != 0) {
		SDL_Log("Text konnte nicht kopiert werden! SDL_Error Error: %s\n", SDL_GetError());
		SDL_FreeSurface(promptSurface);
		SDL_FreeSurface(promptSurface_converted);
		return -1;
	}
	SDL_FreeSurface(promptSurface);
	SDL_FreeSurface(promptSurface_converted);
	
	return 0;
}


	
