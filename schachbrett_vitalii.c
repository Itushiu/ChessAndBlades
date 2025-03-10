#include <stdio.h>

struct figure {
    char farbe;
    char type;
};

int main(void) {
    int zeile;
    int reihe;
    

    // Schachbrett 8x8 mit leeren Figuren initialisieren
    struct figure schachbrett[8][8];
    for (zeile = 0; zeile < 8; zeile++) {         
        for (reihe = 0; reihe < 8; reihe++) {
            schachbrett[zeile][reihe].type = ' ';
            schachbrett[zeile][reihe].farbe = ' ';
        }
    }

    // Standardfiguren einfügen
    for (reihe = 0; reihe < 8; reihe++) {
        schachbrett[1][reihe].type = 'P';
        schachbrett[6][reihe].type = 'P';
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
    
    // Schwarze Farbe für erste beiden Reihen
    for (zeile = 6; zeile < 8; zeile++) {
        for (reihe = 0; reihe < 8; reihe++) {
            schachbrett[zeile][reihe].farbe = 's';
        }
    }

    // Weiße Farbe für letzte beiden Reihen
    for (zeile = 0; zeile < 2; zeile++) {
        for (reihe = 0; reihe < 8; reihe++) {
            schachbrett[zeile][reihe].farbe = 'w';
        }
    }
    
    // Schachbrett ausgeben
    for (zeile = 7; zeile >= 0; zeile--) {
        printf("%d ", zeile+1);
        for (reihe = 0; reihe < 8; reihe++) {
            printf("[%c-%c]", schachbrett[zeile][reihe].type, schachbrett[zeile][reihe].farbe);
        }
        printf("\n");
    }
    for (reihe = 0; reihe < 8; reihe++) {
        printf("    %c", reihe+65);
    }
    printf("\n");

    return(0);

}