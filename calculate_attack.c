#include <stdio.h>
#include "general_structures.h"
#include <stdlib.h>

int calculate_attack(piece_t board [8][8], int move[4]) {
    int rolled_number = rand() % (20 + 1 - 1) + 1; // rand() % (max_number + 1 - minimum_number) + minimum_number
    int stat_difference = board[move[0]][move[1]].attack - board[move[2]][move[3]].defence;
    int damage;
    int damage_formula_1 = ((10 - (stat_difference)) + ((20 - (10 - (stat_difference))) / 3)); 
    int damage_formula_2 = ((10 - (stat_difference)) + ((20 - (10 - (stat_difference))) / 3 * 2));
    int double_damage = 1;

    if (board[move[2]][move[3]].type == ' ') {
        board[move[2]][move[3]] = board[move[0]][move[1]]; // move the figure
        board[move[0]][move[1]].type = ' ';
        board[move[0]][move[1]].color = ' ';
        board[move[0]][move[1]].hp = ' ';
        board[move[0]][move[1]].attack = ' ';
        board[move[0]][move[1]].defence = ' ';
        return (0);
    }

    if (rolled_number >= (10 - stat_difference) && rolled_number != 1) { // successfull attack
        if (rolled_number <= damage_formula_1) { // 1 damage
            damage = 1;
        }
        else if (rolled_number <= damage_formula_2) { // 2 damage
            damage = 2;
        }
        else if (rolled_number < 20) { // 3 damage
            damage = 3;
        }
        else { // 5 damage
            damage = 5;
        }

        board[move[2]][move[3]].hp -= damage; // deal damage

        if (board[move[2]][move[3]].hp <= 0) { // enemy figure died
            printf ("You rolled %d (%d needed) and dealt %d damage to enemy %c, which is now dead!\n",
                rolled_number, (10 - stat_difference), damage, board[move[2]][move[3]].type);
            board[move[2]][move[3]] = board[move[0]][move[1]]; // replace the figure
            board[move[0]][move[1]].type = ' ';
            board[move[0]][move[1]].color = ' ';
            board[move[0]][move[1]].hp = ' ';
            board[move[0]][move[1]].attack = ' ';
            board[move[0]][move[1]].defence = ' ';
            return(1);
        }
        else { // enemy figure still alive
            printf ("You rolled %d (%d needed) and dealt %d damage to enemy %c, which now has %d HP.\n",
                rolled_number, (10 - stat_difference), damage, board[move[2]][move[3]].type, board[move[2]][move[3]].hp);
        }
    }
    else { // unsuccessfull attack
        if (rolled_number == 1) {
            printf ("You rolled 1. Enemy will now counterattack with double damage!\n");
            double_damage = 2; 
        }
        else {
            printf ("You rolled %d (%d needed). Enemy will now counterattack!\n", 
                rolled_number, (10 - stat_difference));
            }

        rolled_number = rand() % (20 + 1 - 1) + 1;
        stat_difference = board[move[2]][move[3]].attack - board[move[0]][move[1]].defence;
        damage_formula_1 = ((10 - (stat_difference)) + ((20 - (10 - (stat_difference))) / 3)); 
        damage_formula_2 = ((10 - (stat_difference)) + ((20 - (10 - (stat_difference))) / 3 * 2));

        if (rolled_number >= (10 - stat_difference) && rolled_number != 1) { // successfull counterattack
            if (rolled_number <= damage_formula_1) { // 1 damage
                damage = 1;
            }
            else if (rolled_number <= damage_formula_2) { // 2 damage
                damage = 2 * double_damage;
            }
            else if (rolled_number < 20) { // 3 damage
                damage = 3 * double_damage;
            }
            else { // 5 damage
                damage = 5 * double_damage;
            }

            board[move[0]][move[1]].hp -= damage; // deal damage

            if (board[move[0]][move[1]].hp <= 0) { // your figure died
                printf ("Enemy rolled %d (%d needed) and dealt %d damage to your %c, which is now dead!\n",
                rolled_number, (10 - stat_difference), damage, board[move[0]][move[1]].type);
                board[move[0]][move[1]] = board[move[2]][move[3]]; // replace the figure
                board[move[2]][move[3]].type = ' ';
                board[move[2]][move[3]].color = ' ';
                board[move[2]][move[3]].hp = ' ';
                board[move[2]][move[3]].attack = ' ';
                board[move[2]][move[3]].defence = ' ';
                return(2);
            }
            else { // your figure still alive
                printf ("Enemy rolled %d (%d needed) and dealt %d damage to your %c, which now has %d HP.\n",
                    rolled_number, (10 - stat_difference), damage, board[move[0]][move[1]].type, board[move[0]][move[1]].hp);
            }
        }
        else {
            printf ("Enemy rolled %d (%d needed) and couldn't counterattack you!\n", rolled_number, (10 - stat_difference));   
        }
    }
    
    return(0);
}