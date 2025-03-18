#include "functions.h"
#include "general_structures.h"

extern text_box_t text_box;
extern char text_box_buffer[500];

int calculate_attack(piece_t board [8][8], int move[4]) {
    srand(time(NULL)); // random seed from current time
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
            snprintf(text_box_buffer, 500, "You rolled %d (%d needed) and dealt %d damage to enemy %c, which is now dead!",
                rolled_number, (10 - stat_difference), damage, board[move[2]][move[3]].type);
            text_box_add(&text_box, text_box_buffer);
            board[move[2]][move[3]] = board[move[0]][move[1]]; // replace the figure
            board[move[0]][move[1]].type = ' ';
            board[move[0]][move[1]].color = ' ';
            board[move[0]][move[1]].hp = ' ';
            board[move[0]][move[1]].attack = ' ';
            board[move[0]][move[1]].defence = ' ';
            return(1);
        }
        else { // enemy figure still alive
            snprintf(text_box_buffer, 500, "You rolled %d (%d needed) and dealt %d damage to enemy %c, which now has %d HP.",
                rolled_number, (10 - stat_difference), damage, board[move[2]][move[3]].type, board[move[2]][move[3]].hp);
            text_box_add(&text_box, text_box_buffer);
        }
    }
    else { // unsuccessfull attack
        if (rolled_number == 1) {
            snprintf(text_box_buffer, 500, "You rolled 1. Enemy will now counterattack with double damage!");
            text_box_add(&text_box, text_box_buffer);
            double_damage = 2; 
        }
        else {
            snprintf(text_box_buffer, 500, "You rolled %d (%d needed). Enemy will now counterattack!", 
                rolled_number, (10 - stat_difference));
            text_box_add(&text_box, text_box_buffer);   
            }

        rolled_number = rand() % (20 + 1 - 1) + 1;
        stat_difference = board[move[2]][move[3]].attack - board[move[0]][move[1]].defence;
        damage_formula_1 = ((10 - (stat_difference)) + ((20 - (10 - (stat_difference))) / 3)); 
        damage_formula_2 = ((10 - (stat_difference)) + ((20 - (10 - (stat_difference))) / 3 * 2));

        if (rolled_number >= (10 - stat_difference) && rolled_number != 1) { // successfull counterattack
            if (rolled_number <= damage_formula_1) { // 1 damage
                damage = 1 * double_damage;
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
                snprintf(text_box_buffer, 500, "Enemy rolled %d (%d needed) and dealt %d damage to your %c, which is now dead!",
                rolled_number, (10 - stat_difference), damage, board[move[0]][move[1]].type);
                text_box_add(&text_box, text_box_buffer);
                board[move[0]][move[1]] = board[move[2]][move[3]]; // replace the figure
                board[move[2]][move[3]].type = ' ';
                board[move[2]][move[3]].color = ' ';
                board[move[2]][move[3]].hp = ' ';
                board[move[2]][move[3]].attack = ' ';
                board[move[2]][move[3]].defence = ' ';
                return(2);
            }
            else { // your figure still alive
                snprintf(text_box_buffer, 500, "Enemy rolled %d (%d needed) and dealt %d damage to your %c, which now has %d HP.",
                    rolled_number, (10 - stat_difference), damage, board[move[0]][move[1]].type, board[move[0]][move[1]].hp);
                text_box_add(&text_box, text_box_buffer);
            }
        }
        else {
            snprintf(text_box_buffer, 500, "Enemy rolled %d (%d needed) and couldn't counterattack you!", rolled_number, (10 - stat_difference));
            text_box_add(&text_box, text_box_buffer); 
        }
    }
    
    return(0);
}