#ifndef GENERAL_STRUCTURES
#define GENERAL_STRUCTURES

typedef struct {
    char color;         // {'w', 'b'}
    char type;          // {'P', 'R', 'B', 'H', 'Q', 'K'}
    int hp;             // {}
    int attack;         // {}
    int defence;        // {}
    int ultimate;       // {}
} piece_t;

typedef struct {
    char text[15][100];
    int count;
} text_box_t;

//for sdl window
//SDL_Window *window;
//SDL_Surface *surface;

#endif