#include "functions.h"
#include "general_structures.h"

extern text_box_t text_box;
extern char text_box_buffer[500];
extern piece_t board[8][8];

void text_box_add(text_box_t *text_box, const char* text) {

    int text_len = strlen(text);
    int start = 0;

    while (start < text_len) {

        char temp[57];
        strncpy(temp, text + start, 56); // extract a string of length 57, start as position in array
        temp[56] = '\0';  // null termination at the end

        if (text_box->count < 32) {
            // just add new line
            strncpy(text_box->text[text_box->count], temp, 57);
            text_box->count++;
        } else {
            // move all lines up if full
            for (int i = 0; i < 32 - 1; i++) {
                strcpy(text_box->text[i], text_box->text[i + 1]);
            }
            // add new line at the bottom
            strncpy(text_box->text[32 - 1], temp, 57);
        }
        start += 56;
    }

    if (text_box->count < 32) {
        // just add new empty line
        text_box->text[text_box->count][0] = ' ';  // so the line is not NULL
        text_box->text[text_box->count][1] = '\0';  // null termination at the end
        text_box->count++;
    } else {
        // move all lines up if full
        for (int i = 0; i < 32 - 1; i++) {
            strcpy(text_box->text[i], text_box->text[i + 1]);
        }
        // add new empty line at the bottom
        text_box->text[31][0] = ' '; // so the line is not NULL
        text_box->text[31][1] = '\0'; // null termination at the end
    }

    SDL_render(board);
}