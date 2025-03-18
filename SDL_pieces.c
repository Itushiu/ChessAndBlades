#include "functions.h"
#include "general_structures.h"

// Globale Variablen das in allen Dateien gleiche größe ist
extern SDL_Window *window;
extern SDL_Surface *surface;


int SDL_pieces(piece_t board[8][8]) {
    int rect_size = 90;
    
    int flags = IMG_INIT_PNG; // Flags für die Initialisierung von SDL_Image

    //image_black_pawn is a pointer to an SDL_Surface object that contains the picture of a black pawn
    SDL_Surface *image_black_pawn = IMG_Load("chess_figures/black_pawn.png");
    if (image_black_pawn == NULL) {
        SDL_Log("Image not loaded%s\n", IMG_GetError());
        return -1;
    }

    //in the following SDL_Surface objects are created for all the chess figures
    SDL_Surface *image_white_pawn = IMG_Load("chess_figures/white_pawn.png");
    if (image_white_pawn == NULL) {
        SDL_Log("Image not loaded%s\n", IMG_GetError());
        return -1;
    }

    SDL_Surface *image_black_rook = IMG_Load("chess_figures/black_rook.png");
    if (image_black_rook == NULL) {
        SDL_Log("Image not loaded%s\n", IMG_GetError());
        return -1;
    }

    SDL_Surface *image_white_rook = IMG_Load("chess_figures/white_rook.png");
    if (image_white_rook == NULL) {
        SDL_Log("Image not loaded%s\n", IMG_GetError());
        return -1;
    }

    SDL_Surface *image_black_horse = IMG_Load("chess_figures/black_horse.png");
    if (image_black_horse == NULL) {
        SDL_Log("Image not loaded%s\n", IMG_GetError());
        return -1;
    }

    SDL_Surface *image_white_horse = IMG_Load("chess_figures/white_horse.png");
    if (image_white_horse == NULL) {
        SDL_Log("Image not loaded%s\n", IMG_GetError());
        return -1;
    }

    SDL_Surface *image_black_bishop = IMG_Load("chess_figures/black_bishop.png");
    if (image_black_bishop == NULL) {
        SDL_Log("Image not loaded%s\n", IMG_GetError());
        return -1;
    }

    SDL_Surface *image_white_bishop = IMG_Load("chess_figures/white_bishop.png");
    if (image_white_bishop == NULL) {
        SDL_Log("Image not loaded%s\n", IMG_GetError());
        return -1;
    }

    SDL_Surface *image_black_queen = IMG_Load("chess_figures/black_queen.png");
    if (image_black_queen == NULL) {
        SDL_Log("Image not loaded%s\n", IMG_GetError());
        return -1;
    }

    SDL_Surface *image_white_queen = IMG_Load("chess_figures/white_queen.png");
    if (image_white_queen == NULL) {
        SDL_Log("Image not loaded%s\n", IMG_GetError());
        return -1;
    }

    SDL_Surface *image_black_king = IMG_Load("chess_figures/black_king.png");
    if (image_black_king == NULL) {
        SDL_Log("Image not loaded%s\n", IMG_GetError());
        return -1;
    }

    SDL_Surface *image_white_king = IMG_Load("chess_figures/white_king.png");
    if (image_white_king == NULL) {
        SDL_Log("Image not loaded%s\n", IMG_GetError());
        return -1;
    }

//in the following for loops are created that create SDL_Rect objects for the pawns with the correct coordinates and sizes for the images 
//and then print them on the surface

	for (int i=0; i < 8; i++){
		for (int j=0; j < 8; j++){
			if (board[i][j].color == 'b' && board[i][j].type == 'P'){
				SDL_Rect image_rect_black_pawn = {
            		.x = 5 + i * rect_size, // Beispiel: Bild in der x Spalte
            		.y = 5 + (7-j) * rect_size, // Bild in der 2. Reihe
           		 	.w = image_black_pawn->w, // Breite des Bildes
            		.h = image_black_pawn->h // Höhe des Bildes
       			 };
				SDL_BlitSurface(image_black_pawn, NULL, surface, &image_rect_black_pawn);
			}

			else if (board[i][j].color == 'b' && board[i][j].type == 'R'){
				SDL_Rect image_rect_black_rook = {
            		.x = 5 + i * rect_size, // Beispiel: Bild in der x Spalte
            		.y = 5 + (7-j) * rect_size, // Bild in der 2. Reihe
           		 	.w = image_black_rook->w, // Breite des Bildes
            		.h = image_black_rook->h // Höhe des Bildes
        		};
        	SDL_BlitSurface(image_black_rook, NULL, surface, &image_rect_black_rook);
			}

			else if (board[i][j].color == 'b' && board[i][j].type == 'H'){
				SDL_Rect image_rect_black_horse = {
            		.x = 5 + i * rect_size , // Beispiel: Bild in der x Spalte
            		.y = 5 + (7-j) * rect_size, // Bild in der 2. Reihe
           		 	.w = image_black_horse->w, // Breite des Bildes
            		.h = image_black_horse->h // Höhe des Bildes
        		};
        	SDL_BlitSurface(image_black_horse, NULL, surface, &image_rect_black_horse);
			}

			else if (board[i][j].color == 'b' && board[i][j].type == 'B'){
				SDL_Rect image_rect_black_bishop = {
            		.x = 5 + i * rect_size, // Beispiel: Bild in der x Spalte
            		.y = 5 + (7-j) * rect_size, // Bild in der 2. Reihe
           		 	.w = image_black_bishop->w, // Breite des Bildes
            		.h = image_black_bishop->h // Höhe des Bildes
        		};
        	SDL_BlitSurface(image_black_bishop, NULL, surface, &image_rect_black_bishop);
			}

			else if (board[i][j].color == 'b' && board[i][j].type == 'Q'){
				SDL_Rect image_rect_black_queen = {
            		.x = 5 + i * rect_size, // Beispiel: Bild in der x Spalte
            		.y = 5 + (7-j) * rect_size, // Bild in der 2. Reihe
           		 	.w = image_black_queen->w, // Breite des Bildes
            		.h = image_black_queen->h // Höhe des Bildes
        		};
        	SDL_BlitSurface(image_black_queen, NULL, surface, &image_rect_black_queen);
			}

			else if (board[i][j].color == 'b' && board[i][j].type == 'K'){
				SDL_Rect image_rect_black_king = {
            		.x = 5 + i * rect_size, // Beispiel: Bild in der x Spalte
            		.y = 5 + (7-j) * rect_size, // Bild in der 2. Reihe
           		 	.w = image_black_king->w, // Breite des Bildes
            		.h = image_black_king->h // Höhe des Bildes
        		};
        	SDL_BlitSurface(image_black_king, NULL, surface, &image_rect_black_king);
			}

			else if (board[i][j].color == 'w' && board[i][j].type == 'P'){
				SDL_Rect image_rect_white_pawn = {
            		.x = 5 + i * rect_size, // Beispiel: Bild in der x Spalte
            		.y = 5 + (7-j) * rect_size, // Bild in der 2. Reihe
           		 	.w = image_white_pawn->w, // Breite des Bildes
            		.h = image_white_pawn->h // Höhe des Bildes
       			 };
				SDL_BlitSurface(image_white_pawn, NULL, surface, &image_rect_white_pawn);
			}

			else if (board[i][j].color == 'w' && board[i][j].type == 'R'){
				SDL_Rect image_rect_white_rook = {
            		.x = 5 + i * rect_size, // Beispiel: Bild in der x Spalte
            		.y = 5 + (7-j) * rect_size, // Bild in der 2. Reihe
           		 	.w = image_white_rook->w, // Breite des Bildes
            		.h = image_white_rook->h // Höhe des Bildes
       			 };
				SDL_BlitSurface(image_white_rook, NULL, surface, &image_rect_white_rook);
			}

			else if (board[i][j].color == 'w' && board[i][j].type == 'H'){
				SDL_Rect image_rect_white_horse = {
            		.x = 5 + i * rect_size, // Beispiel: Bild in der x Spalte
            		.y = 5 + (7-j) * rect_size, // Bild in der 2. Reihe
           		 	.w = image_white_horse->w, // Breite des Bildes
            		.h = image_white_horse->h // Höhe des Bildes
       			 };
				SDL_BlitSurface(image_white_horse, NULL, surface, &image_rect_white_horse);
			}

			else if (board[i][j].color == 'w' && board[i][j].type == 'B'){
				SDL_Rect image_rect_white_bishop = {
            		.x = 5 + i * rect_size, // Beispiel: Bild in der x Spalte
            		.y = 5 + (7-j) * rect_size, // Bild in der 2. Reihe
           		 	.w = image_white_bishop->w, // Breite des Bildes
            		.h = image_white_bishop->h // Höhe des Bildes
       			 };
				SDL_BlitSurface(image_white_bishop, NULL, surface, &image_rect_white_bishop);
			}

			else if (board[i][j].color == 'w' && board[i][j].type == 'Q'){
				SDL_Rect image_rect_white_queen = {
            		.x = 5 + i * rect_size, // Beispiel: Bild in der x Spalte
            		.y = 5 + (7-j) * rect_size , // Bild in der 2. Reihe
           		 	.w = image_white_queen->w, // Breite des Bildes
            		.h = image_white_queen->h // Höhe des Bildes
       			 };
				SDL_BlitSurface(image_white_queen, NULL, surface, &image_rect_white_queen);
			}

			else if (board[i][j].color == 'w' && board[i][j].type == 'K'){
				SDL_Rect image_rect_white_king = {
            		.x = 5 + i * rect_size, // Beispiel: Bild in der x Spalte
            		.y = 5 + (7-j) * rect_size, // Bild in der 2. Reihe
           		 	.w = image_white_king->w, // Breite des Bildes
            		.h = image_white_king->h // Höhe des Bildes
       			 };
				SDL_BlitSurface(image_white_king, NULL, surface, &image_rect_white_king);
			}
		}
	}
    SDL_FreeSurface(image_black_pawn); // Freigabe des Bildes
    SDL_FreeSurface(image_white_pawn); // Freigabe des Bildes
    SDL_FreeSurface(image_black_rook); // Freigabe des Bildes
    SDL_FreeSurface(image_white_rook); // Freigabe des Bildes
    SDL_FreeSurface(image_black_horse); // Freigabe des Bildes
    SDL_FreeSurface(image_white_horse); // Freigabe des Bildes
    SDL_FreeSurface(image_black_bishop); // Freigabe des Bildes
    SDL_FreeSurface(image_white_bishop); // Freigabe des Bildes
    SDL_FreeSurface(image_black_queen); // Freigabe des Bildes
    SDL_FreeSurface(image_white_queen); // Freigabe des Bildes
    SDL_FreeSurface(image_black_king); // Freigabe des Bildes
    SDL_FreeSurface(image_white_king); // Freigabe des Bildes
    return 0;
}