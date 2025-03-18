#include "functions.h"
#include "general_structures.h"

void text_box_add(text_box_t *text_box, const char* text) {
    if (text_box->count < 15) {
        // just add new line
        strncpy(text_box->text[text_box->count], text, 100);
        text_box->text[text_box->count][100 - 1] = '\0';  // make sure to put end of string
        text_box->count++;
    } else {
        // move all lines up if full
        for (int i = 0; i < 15 - 1; i++) {
            strcpy(text_box->text[i], text_box->text[i + 1]);
        }
        // add new line at the bottom
        strncpy(text_box->text[15 - 1], text, 100);
        text_box->text[15 - 1][100 - 1] = '\0';
    }
}