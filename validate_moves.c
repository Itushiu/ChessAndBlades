#include <stdio.h>
#include <stdlib.h>
#include "general_structures.h"

/*  Describes the functions to validate the moves of the different chess pieces
    returns 0 if the move is valid, 1 if the move is invalid
    start[] and end[] are arrays with the x and y coordinates of the start and end position of the piece
    An input of coordiantes without an actual change are ruled invalid as well. There's no dealing with collisions. */

// QUESTIONS: why double else in the end of r & b

//Rook
int validate_move_r(int move[4], piece_t board[8][8]){
    if ((move[0] == move[2]) && (move[1] != move[3])) { //only one of the coordinates may change for a valid rook move
        if (move[1] < move[3]) { // check if someone on the way
            for (int i = move[1]+1; i < move[3]; i++) {
                if (board[move[0]][i].type != ' ') {
                    return 0;
                }
            }
        } else {
            for (int i = move[1]-1; i > move[3]; i--) {
                if (board[move[0]][i].type != ' ') {
                    return 0;
                }
            }   
        }
        return 1;
    } else if ((move[1] == move[3]) && (move[0] != move[2])) {
        if (move[0] < move[2]) { // check if someone on the way
            for (int i = move[0]+1; i < move[2]; i++) {
                if (board[i][move[1]].type != ' ') {
                    return 0;
                }
            }
        } else {
            for (int i = move[0]-1; i > move[2]; i--) {
                if (board[i][move[1]].type != ' ') {
                    return 0;
                }
            }   
        }
        return 1;
    } else {
        return 0;
    }
}

//Bishop
int validate_move_b(int move[4], piece_t board[8][8]){
    //for a valid bishop move, the absolute value of the change in the coordinates must be equal for both coordinates
    if ((abs(move[0] - move[2]) == abs(move[1] - move[3])) && (move[0] != move[2])) {
        if (move[0] > move[2] && move[1] > move[3]) { // check if someone on the way
            for (int i = move[0]-1, j = move[1]-1; i > move[2] && j > move[3]; i--, j--) {
                if (board[i][j].type != ' ') {
                    return 0;
                }
            }
        }
        else if (move[0] < move[2] && move[1] > move[3]) { // check if someone on the way
            for (int i = move[0]+1, j = move[1]-1; i < move[2] && j > move[3]; i++, j--) {
                if (board[i][j].type != ' ') {
                    return 0;
                }
            }
        }  
        else if (move[0] > move[2] && move[1] < move[3]) { // check if someone on the way
            for (int i = move[0]-1, j = move[1]+1; i > move[2] && j < move[3]; i--, j++) {
                if (board[i][j].type != ' ') {
                    return 0;
                }
            }
        }  
        else { // check if someone on the way
            for (int i = move[0]+1, j = move[1]+1; i < move[2] && j < move[3]; i++, j++) {
                if (board[i][j].type != ' ') {
                    return 0;
                }
            }
        }
        return 1;
    } else {
        return 0;
    }
}

//Horse
int validate_move_h(int move[4], piece_t board[8][8]){
    //a horse move is valid if it's NOT a valid bishop or rook move AND the piece moves exactly 3 fields
    if (!((move[0] == move[2]) && (move[1] != move[3])) && !((move[1] == move[3]) && (move[0] != move[2])) && !((abs(move[0] - move[2]) == abs(move[1] - move[3])) && (move[0] != move[2])) && (abs(move[0] - move[2]) + abs(move[1] - move[3]) == 3)) {
        return 1;
    } else {
        return 0;
    }
}

//Queen
int validate_move_q(int move[4], piece_t board[8][8]){
    //the queen unites the moving ability of a rook and a bishop
    // CHANGED:possible wrong syntax: Is it possible to convert 0 to 1 with the operator !0 ? Otherwise we could write validate_move_r == 0 etc.
    if (validate_move_r(move, board) || validate_move_b(move, board)) {
        return 1;
    } else {
        return 0;
    }
}

//King
int validate_move_k(int move[4], piece_t board[8][8]){
    //the king can move one field in any direction
    if (abs(move[0] - move[2]) <= 1 && abs(move[1] - move[3]) <= 1) {
        return 1;
    } else {
        return 0;
    }
}

//Pawn
int validate_move_p_black(int move[4], piece_t board[8][8]){
    if ((move[1]-1 == move[3]) && (move[0]+1 == move[2]) && board[move[2]][move[3]].type != ' ') { // for eating as pawn r
        return 1;
    }
    else if ((move[1]-1 == move[3]) && (move[0]-1 == move[2]) && board[move[2]][move[3]].type != ' ') { // for eating as pawn l
        return 1;
    }
    else if ((move[0] == move[2]) && (move[1]-1) == move[3]) { //2nd coordinate is decreased by 1
        return 1; //valid move for black pawn
    }
    else if((move[1] == 6) && (move[0] == move[2]) && ((move[1]-2) == move[3])) { //black pawn is in standard position and moves 2 fields
        if (board[move[0]][move[1]-1].type != ' ') { // check if someone on the way
            return 0;
        } 
        return 1;
    } else { //intial dash is ruled valid if black pawn was in standard position
        return 0;
    } 
}
    


int validate_move_p_white(int move[4], piece_t board[8][8]){
    if ((move[1]+1 == move[3]) && (move[0]+1 == move[2]) && board[move[2]][move[3]].type != ' ') { // for eating as pawn r
        return 1;
    }
    else if ((move[1]+1 == move[3]) && (move[0]-1 == move[2]) && board[move[2]][move[3]].type != ' ') { // for eating as pawn l
        return 1;
    }
    else if ((move[0] == move[2]) && (move[1] + 1) == move[3]) { //2nd coordinate is increased by 1
        return 1; //valid move for white pawn
    }
    else if((move[1] == 1) && (move[0] == move[2]) && ((move[1]+2) == move[3])) { //white pawn is in standard position and moves 2 fields
        if (board[move[0]][move[1]+1].type != ' ') { // check if someone on the way
            return 0;
        } 
        return 1;
    } else { //intial dash is ruled valid if white pawn was in standard position
        return 0;
    } 
}
    


int validate_moves(piece_t board[8][8], int move[4]) {
    switch (board[move[0]][move[1]].type) {
        case 'R':
            if (validate_move_r(move, board)) {
                return 1;
            } else {
                return 0;
            }
            break;
        case 'Q':
            if (validate_move_q(move, board)) {
                return 1;
            } else {
                return 0;
            }
            break;
        case 'K':
            if (validate_move_k(move, board)) {
                return 1;
            } else {
                return 0;
            }
            break;
        case 'H':
            if (validate_move_h(move, board)) {
                return 1;
            } else {
                return 0;
            }
            break;
        case 'B':
            if (validate_move_b(move, board)) {
                return 1;
            } else {
                return 0;
            }
            break;
        case 'P':
            if (board[move[0]][move[1]].color == 'b') {
                if (validate_move_p_black(move, board)) {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                if (validate_move_p_white(move, board)) {
                    return 1;
                } else {
                    return 0;
                }
            }
            break;
        case ' ':
            return 0;
            break;
    }
}