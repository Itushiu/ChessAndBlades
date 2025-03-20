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
    char text[32][57];
    int count;
} text_box_t;

enum screen_size {
    SCREEN_WIDTH = 1400,
    SCREEN_HEIGHT = 820,
};

//for sdl window
//SDL_Window *window;
//SDL_Surface *surface;

#endif