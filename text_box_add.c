#include "functions.h"
#include "general_structures.h"

extern text_box_t text_box;
extern char text_box_buffer[500];
extern piece_t board[8][8];

void text_box_add(text_box_t *text_box, const char* text) {

    int text_len = strlen(text);
    int start = 0;

    while (start < text_len) {

        int end = start + 56; // end for current line

        if (end >= text_len) { // if string is shorter than 56 - no wrapping needed
            end = text_len;
        } else {
            // don't split words, find the last space before the end
            while (end > start && text[end] != ' ') {
                end--;
            }

            // if no space was found, split the word
            if (end == start) {
                end = start + 56;
            }
        }

        char temp[57];
        int copy_length = end - start; // how much should we copy into current line    
        strncpy(temp, text + start, copy_length); // extract a string of needed length, start as position in array
        temp[copy_length] = '\0';  // null termination at the end

        if (text[end] == ' ') { // skip space at the start of next line
            start = end + 1;
        } else {
            start = end;
        }

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

    SDL_init_text();
}