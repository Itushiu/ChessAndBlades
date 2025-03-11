#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Describes the functions to validate the moves of the different chess pieces
    returns 0 if the move is valid, 1 if the move is invalid
    start[] and end[] are arrays with the x and y coordinates of the start and end position of the piece
    An input of coordiantes without an actual change are ruled invalid as well. There's no dealing with collisions. */

//Rook
int validate_move_r(int start[], int end[]){
    if ((start[0] == end[0]) && (start[1] != end[1])) { //only one of the coordinates may change for a valid rook move
        return 0;
    } else if ((start[1] == end[1]) && (start[0] != end[0])) {
        return 0;
    } else {
        return 1;
    }
}

//Bishop
int validate_move_b(int start[], int end[]){
    //for a valid bishop move, the absolute value of the change in the coordinates must be equal for both coordinates
    if ((abs(start[0] - end[0]) == (abs(start[1] - end[1]))) && ((start[0] == end[0]) != 0)) {
        return 0;
    } else {
        return 1;
    }
}

//Horse
int validate_move_h(int start[], int end[]){
    //a horse move is valid if it's NOT a valid bishop or rook move AND the piece moves exactly 3 fields
    if (validate_move_r(start[], end[]) && validate_move_b(start[], end[]) && (abs(start[0] - end[0]) + abs(start[1] - end[1]) == 3)) {
        return 0;
    } else {
        return 1;
    }
}

//Queen
int validate_move_q(int start[], int end[]){
    //the queen unites the moving ability of a rook and a bishop
    //possible wrong syntax: Is it possible to convert 0 to 1 with the operator !0 ? Otherwise we could write validate_move_r == 0 etc.
    if (!(validate_move_r(start[], end[])) || !(validate_move_b(start[], end[]))) {
        return 0;
    } else {
        return 1;
    }
}

//King
int validate_move_k(int start[], int end[]){
    //the king can move one field in any direction
    if (abs(start[0] - end[0]) <= 1 && abs(start[1] - end[1]) <= 1) {
        return 0;
    } else {
        return 1;
    }
}

//Pawn
int validate_move_p_black(int start[], int end[], char board[][]){
    //if(!(strcmp(board[start[0]][start[1]].color, 'b'))) { //we have a black piece ('b' might still be called 's' elsewhere)
    //abfrage wahrscheinlich unnötig, da schon in switch case abgefraft wird
        if ((start[0] == end[0]) && (start[1]-1) == end[1]) { //2nd coordinate is decreased by 1
            return 0; //valid move for black pawn
        }
        if((start[1] == 7) && (start[0] == end[0]) && ((start[1]-2) == end[1])) { //black pawn is in standard position and moves 2 fields
            return 0;
        } //intial dash is ruled valid if black pawn was in standard position
    }
    else{
        return 1;
    }
//}

int validate_move_p_white(int start[], int end[], char board[][]){
    //if(!(strcmp(board[start[0]][start[1]].color, 'w'))) { //we have a white piece
        if ((start[0] == end[0]) && (start[1] + 1) == end[1]) { //2nd coordinate is increased by 1
            return 0; //valid move for white pawn
        }
        if((start[1] == 2) && (start[0] == end[0]) && ((start[1]+2) == end[1])) { //white pawn is in standard position and moves 2 fields
            return 0;
        } //intial dash is ruled valid if white pawn was in standard position
    }
    else{
        return 1;
    }
//}