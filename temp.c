#include "general_structures.h"  // Assumes piece_t is defined here (e.g., typedef struct { char type; char color; } piece_t;)
#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>

enum { SCREEN_WIDTH = 640, SCREEN_HEIGHT = 640 };
const int SQUARE_SIZE = 80;

// Function prototypes for game logic (implement these in your project)
int init_chessboard(piece_t board[8][8]);    // Set up pieces in initial positions
int print_board(piece_t board[8][8]);          // Optionally print board state to console
int get_input(int move[4], piece_t board[8][8], char current_player); // Get move from user (e.g., via console input)
int validate_moves(piece_t board[8][8], int move[4]);
int make_move(piece_t board[8][8], int move[4]);


int row;
int column;

// Render the chess board and pieces using SDL
void render_board(SDL_Surface *surface, piece_t board[8][8]) {
    // Define colors for the board squares
    Uint32 light = SDL_MapRGB(surface->format, 240, 217, 181);
    Uint32 dark  = SDL_MapRGB(surface->format, 181, 136, 99);
    
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            SDL_Rect square = { col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
            // Alternate square colors
            if ((row + col) % 2 == 0)
                SDL_FillRect(surface, &square, light);
            else
                SDL_FillRect(surface, &square, dark);
            
            // Draw the piece if there is one
            if (board[row][col].type != ' ') {
                // Choose piece color based on piece color ('w' for white, 'b' for black)
                Uint32 pieceColor = (board[row][col].color == 'w')
                                    ? SDL_MapRGB(surface->format, 255, 255, 255)
                                    : SDL_MapRGB(surface->format, 0, 0, 0);
                // Draw a smaller rectangle in the center of the square to represent the piece
                SDL_Rect pieceRect = { col * SQUARE_SIZE + SQUARE_SIZE / 4,
                                       row * SQUARE_SIZE + SQUARE_SIZE / 4,
                                       SQUARE_SIZE / 2, SQUARE_SIZE / 2 };
                SDL_FillRect(surface, &pieceRect, pieceColor);
            }
        }
    }
}

int main(void) {

    piece_t board[8][8];
    // Initialize board with starting positions
    init_chessboard(board);
    // Optionally print the board to the console for debugging
    print_board(board);
    
    // Initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }
    
    // Create an SDL window
    SDL_Window *window = SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    // Get the window's drawing surface
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    
    int move[4];
    char current_player = 'w';
    bool quit = false;
    SDL_Event e;
    
    // Render the initial board state
    render_board(surface, board);
    SDL_UpdateWindowSurface(window);
    
    // Main game loop
    while (!quit) {
        // Process SDL events (e.g., window close)
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }
        if (quit)
            break;
        
        // Get the move from the user (this could be via console input)
        get_input(move, board, current_player);
        
        // Validate the move according to your game rules
        if (validate_moves(board, move)) {
            // Prevent capturing a piece from the same team
            if (board[move[2]][move[3]].type != ' ' &&
                board[move[2]][move[3]].color == board[move[0]][move[1]].color) {
                printf("Don't eat your team 😜\n");
            } else {
                // Make the move
                make_move(board, move);
                // Switch the current player after a successful move
                current_player = (current_player == 'w') ? 'b' : 'w';
            }
        } else {
            printf("Not a valid move for %c\n", board[move[0]][move[1]].type);
        }
        
        // Update the board display after each move
        render_board(surface, board);
        SDL_UpdateWindowSurface(window);
    }
    
    // Clean up SDL resources
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
