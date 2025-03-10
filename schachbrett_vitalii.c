#include <stdio.h>

struct figure {
    char farbe;
    char type;
};


int main(void) {
    int row;
    int column;
    
    struct figure schachbrett[8][8];
    

    for (row = 0; row < 8; row++) {
        for (column = 0; column < 8; column++) {
            schachbrett[row][column].type = ' ';
            schachbrett[row][column].farbe = ' ';
        }
    }

    for (column = 0; column < 8; column++) {
        schachbrett[1][column].type = 'P';
        schachbrett[6][column].type = 'P';
    }

    schachbrett[0][0].type = 'R';
    schachbrett[0][7].type = 'R';
    schachbrett[7][0].type = 'R';
    schachbrett[7][7].type = 'R';

    schachbrett[0][3].type = 'Q';
    schachbrett[7][3].type = 'Q';

    schachbrett[0][4].type = 'K';
    schachbrett[7][4].type = 'K';

    schachbrett[0][1].type = 'H';
    schachbrett[7][1].type = 'H';
    schachbrett[0][6].type = 'H';
    schachbrett[7][6].type = 'H';

    schachbrett[0][2].type = 'B';
    schachbrett[7][2].type = 'B';
    schachbrett[0][5].type = 'B';
    schachbrett[7][5].type = 'B';



    

    for (row = 0; row < 2; row++) {
        for (column = 0; column < 8; column++) {
            schachbrett[row][column].farbe = 's';
        }
    }

    for (row = 6; row < 8; row++) {
        for (column = 0; column < 8; column++) {
            schachbrett[row][column].farbe = 'w';
        }
    }
    
    for (row = 0; row < 8; row++) {
        for (column = 0; column < 8; column++) {
            printf("[%c-%c]", schachbrett[row][column].type, schachbrett[row][column].farbe);
        }
        printf("\n");
    }



}