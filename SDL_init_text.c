#include "functions.h"
#include "general_structures.h"

// Globale Variablen das in allen Dateien gleiche größe ist
extern SDL_Window *window;
extern SDL_Surface *surface;
extern piece_t board[8][8];

extern text_box_t text_box;

int SDL_init_text(void) {
    int rect_size = 90;

    //Insertion of text on right part of window via sdl_ttf
    //initializing sdl_ttf
    if (TTF_Init() == -1) {
		SDL_Log("SDL_ttf initialization failed! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }

    TTF_Font *font = TTF_OpenFont("Go_Mono.ttf", 28);
    if (font == NULL){
		SDL_Log("Font could not be loaded. SDL_ttf Error: %s\n", TTF_GetError());
		return -1;
	}

    TTF_Font *font2 = TTF_OpenFont("Go_Mono.ttf", 19); // font for log text
    if (font2 == NULL){
		SDL_Log("Font could not be loaded. SDL_ttf Error: %s\n", TTF_GetError());
		return -1;
	}
	
    //Colors for the text
    SDL_Color white_color = {.r = 255, .g = 255, .b = 255, .a = 255};
    SDL_Color black_color = {.r = 0, .g = 0, .b = 0, .a = 255};

   
    for (int i = 0; i < 32; i++) {
        // from text to pixels
        SDL_Surface *text = TTF_RenderText_Solid(font2, text_box.text[i], white_color);
        if (text == NULL) {
            break;
            SDL_Log("Text rendering failed: %s\n", TTF_GetError());
            TTF_CloseFont(font2);
            return -1;
        }

        SDL_Surface *text_konvertiert = SDL_ConvertSurfaceFormat(text, surface->format->format, 0);
        if (text_konvertiert == NULL) {
            SDL_Log("Text couldn't be converted! SDL_Error Error: %s\n", SDL_GetError());
            SDL_FreeSurface(text);
            TTF_CloseFont(font2);
            return -1;
        }
        
        //hier irgendwie kompilierfehler 
        //CHANGE: from *textRect to textRect
        //it's already a "box" with smth inside, *box just gives an address of the box 
        SDL_Rect textRect = {	//creating a rect object for the text to go into
            .x = (8 * rect_size) + 50,		//it should be located at the upper right corner of the window, next to the board
            .y = 22 * i, 
            .w = text_konvertiert->w, 
            .h = text_konvertiert->h
        };
        //CHANGE: textRect --> &textRect
        if (SDL_BlitSurface(text_konvertiert, NULL, surface, &textRect) != 0) {
            SDL_Log("Text couldn't be copied! SDL_Error Error: %s\n", SDL_GetError());
            SDL_FreeSurface(text);
            SDL_FreeSurface(text_konvertiert);
            TTF_CloseFont(font2);
            return -1;
        }

//        SDL_Log("Text position: (%d, %d), size: (%d, %d)", textRect.x, textRect.y, textRect.w, textRect.h);


        SDL_FreeSurface(text); 
        SDL_FreeSurface(text_konvertiert); 
    }

    // Letters A-H unter dem Schachbrett
    const char *letters = "ABCDEFGH";
    for(int i = 0; i < 8; i++) {
        char letter[2] = {letters[i], '\0'};

        SDL_Surface *text = TTF_RenderText_Solid(font, letter, white_color);
        if (text == NULL) {
            SDL_Log("Text rendering failed: %s\n", TTF_GetError());
            return -1;
        }
        
        // Konvertiere die Text-Surface
        SDL_Surface *text_konvertiert = SDL_ConvertSurfaceFormat(text, surface->format->format, 0);
	    if (text_konvertiert == NULL) {
		    SDL_Log("Text couldn't be converted! SDL_Error Error: %s\n", SDL_GetError());
            SDL_FreeSurface(text);
            TTF_CloseFont(font);
            return -1;
    	}
        
        // Positioning from letters
        SDL_Rect letter_rect = {
            .x = i * rect_size + (rect_size/2) - 7, // Zentriert unter jedem Feld
            .y = 5 + 8 * rect_size, // Unter dem Brett
            .w = text_konvertiert->w,
            .h = text_konvertiert->h
        };
    
        // Drawing of the letters
        if (SDL_BlitSurface(text_konvertiert, NULL, surface, &letter_rect)) {
            SDL_Log("Text couldn't be copied! SDL_Error Error: %s\n", SDL_GetError());
            SDL_FreeSurface(text);
            SDL_FreeSurface(text_konvertiert);
            TTF_CloseFont(font);
            return -1;
        }
        
        // Gib die Surfaces frei
        SDL_FreeSurface(text);
        SDL_FreeSurface(text_konvertiert);
    }

    // Zahlen 1-8 links vom Schachbrett
    for (int i=1; i<9; i++) {
        char number[2] = {i + '0', '\0'};
        SDL_Surface *text = TTF_RenderText_Solid(font, number, white_color);
        if (text == NULL) {
            SDL_Log("Number rendering failed: %s\n", TTF_GetError());
            return -1;
        }
        
        // Konvertiere die Text-Surface
        SDL_Surface *number_konvertiert = SDL_ConvertSurfaceFormat(text, surface->format->format, 0);
        if (number_konvertiert == NULL) {
            SDL_Log("Number couldn't be converted! SDL_Error Error: %s\n", SDL_GetError());
            SDL_FreeSurface(text);
            TTF_CloseFont(font);
            return -1;
    	}
        
        // Positioning from numbers
        SDL_Rect number_rect = {
            .x = 8 * rect_size + 10, // Rechts vom Brett
            .y = (8-i) * rect_size + (rect_size - 60) , // Zentriert neben jedem Feld
            .w = number_konvertiert->w,
            .h = number_konvertiert->h
        };
    
        // Drawing of the numbers
        if (SDL_BlitSurface(number_konvertiert, NULL, surface, &number_rect)) {
            SDL_Log("Numbers couldn't be copied! SDL_Error Error: %s\n", SDL_GetError());
            SDL_FreeSurface(text);
            SDL_FreeSurface(number_konvertiert);
            TTF_CloseFont(font);
            return -1;
        }

        // Gib die Surfaces frei
        SDL_FreeSurface(number_konvertiert);
        SDL_FreeSurface(text);
    }

    //Shows if the figure has used its ultimate ability
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(board[i][j].ultimate == 1) {


                SDL_Surface *text = TTF_RenderText_Solid(font2, "U" , black_color);
                if (text == NULL) {
                    SDL_Log("Text rendering failed: %s\n", TTF_GetError());
                    TTF_CloseFont(font2);
                    return -1;
                }

                SDL_Surface *text_konvertiert = SDL_ConvertSurfaceFormat(text, surface->format->format, 0);
                if (text_konvertiert == NULL) {
                    SDL_Log("Text couldn't be converted! SDL_Error Error: %s\n", SDL_GetError());
                    SDL_FreeSurface(text);
                    TTF_CloseFont(font2);
                    return -1;
                }
                
                
                SDL_Rect textRect = {	//creating a rect object for the text to go into
                    .x = i * rect_size + rect_size - 15,
                    .y = (7-j) * rect_size - 1, 
                    .w = text_konvertiert->w, 
                    .h = text_konvertiert->h
                };
                //CHANGE: textRect --> &textRect
                if (SDL_BlitSurface(text_konvertiert, NULL, surface, &textRect) != 0) {
                    SDL_Log("Text couldn't be copied! SDL_Error Error: %s\n", SDL_GetError());
                    SDL_FreeSurface(text);
                    SDL_FreeSurface(text_konvertiert);
                    TTF_CloseFont(font2);
                    return -1;
                }

                SDL_FreeSurface(text); 
                SDL_FreeSurface(text_konvertiert);
            }
        }
    }

    //Shows how much HP each figure has
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(board[i][j].type != ' ') {
                char hp_text[3];
                sprintf(hp_text, "%d", board[i][j].hp);
                SDL_Surface *text = TTF_RenderText_Solid(font2, hp_text , black_color);
                if (text == NULL) {
                    SDL_Log("Text rendering failed: %s\n", TTF_GetError());
                    TTF_CloseFont(font2);
                    return -1;
                }

                SDL_Surface *text_konvertiert = SDL_ConvertSurfaceFormat(text, surface->format->format, 0);
                if (text_konvertiert == NULL) {
                    SDL_Log("Text couldn't be converted! SDL_Error Error: %s\n", SDL_GetError());
                    SDL_FreeSurface(text);
                    TTF_CloseFont(font2);
                    return -1;
                }
                
                
                SDL_Rect textRect = {	//creating a rect object for the text to go into
                    .x = i * rect_size + 2,
                    .y = (7-j) * rect_size - 1, 
                    .w = text_konvertiert->w, 
                    .h = text_konvertiert->h
                };
                //CHANGE: textRect --> &textRect
                if (SDL_BlitSurface(text_konvertiert, NULL, surface, &textRect) != 0) {
                    SDL_Log("Text couldn't be copied! SDL_Error Error: %s\n", SDL_GetError());
                    SDL_FreeSurface(text);
                    SDL_FreeSurface(text_konvertiert);
                    TTF_CloseFont(font2);
                    return -1;
                }

                SDL_FreeSurface(text); 
                SDL_FreeSurface(text_konvertiert);
            }
        }
    }

    TTF_CloseFont(font);
    TTF_CloseFont(font2);
    return 0;
} 