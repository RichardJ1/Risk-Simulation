// simulating an offense vs defense roll in Risk
// offense rolls 3 dice, defense rolls 2 dice
// offense and defense dice are compared in pairs
// higher die wins, ties go to defense

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int roll_die() {
    return rand() % 6 + 1;
}

int battle(int offense_troops, int defense_troops) {
    int offense[offense_troops];
    int defense[defense_troops];

    for(int i = 0; i < offense_troops; i++) {
        offense[i] = roll_die();
    }

    for(int i = 0; i < defense_troops; i++) {
        defense[i] = roll_die();
    }

    // sort the dice rolls in descending order
    for(int i = 0; i < offense_troops; i++) {
        for(int j = i + 1; j < offense_troops; j++) {
            if(offense[j] > offense[i]) {
                int temp = offense[i];
                offense[i] = offense[j];
                offense[j] = temp;
            }
        }
    }

    for(int i = 0; i < defense_troops; i++) {
        for(int j = i + 1; j < defense_troops; j++) {
            if(defense[j] > defense[i]) {
                int temp = defense[i];
                defense[i] = defense[j];
                defense[j] = temp;
            }
        }
    }

    int offense_wins = 0;
    int defense_wins = 0;

    int decider = offense_troops < defense_troops ? offense_troops : defense_troops;

    for(int i = 0; i < decider; i++) {
        if(offense[i] > defense[i]) {
            offense_wins++;
        } else {
            defense_wins++;
        }
    }

    return (offense_wins << 8) | defense_wins;
}

int attack(int o_troops, int d_troops) {
    int offense_starting_troops = o_troops - 1; // number of troops in the attacking territory - 1
    int defense_starting_troops = d_troops; // number of troops in the defending territory



    while (1) {
        int offense_troops_in_battle = offense_starting_troops > 3 ? 3 : offense_starting_troops;
        int defense_troops_in_battle = defense_starting_troops > 2 ? 2 : defense_starting_troops;

        // printf("Offense troops: %d\n", offense_starting_troops);
        // printf("Defense troops: %d\n", defense_starting_troops);


        int result = battle(offense_troops_in_battle, defense_troops_in_battle);

        int offense_wins = (result >> 8) & 0xFF;
        int defense_wins = result & 0xFF;

        offense_starting_troops -= defense_wins;
        defense_starting_troops -= offense_wins;

        if(defense_starting_troops == 0) {
            // printf("Offense wins\n");
            return 1;
        } else if(offense_starting_troops == 0) {
            // printf("Defense wins\n");
            return 0;
        }
    }
    return 0;
}

int main() {
    srand(time(NULL));
    int offense_troops = 10;
    int defense_troops = 3;

    // printf("Enter number of troops in the attacking territory: ");
    // scanf("%d", &offense_troops);

    // printf("Enter number of troops in the defending territory: ");
    // scanf("%d", &defense_troops);

    int offense_wins = 0;
    int defense_wins = 0;

    for (int i = 0; i < 10000; i++) {
        if(attack(offense_troops, defense_troops)) {
            offense_wins++;
        } else {
            defense_wins++;
        }
    }

    printf("Offense wins: %d\n", offense_wins);
    printf("Defense wins: %d\n", defense_wins);


    return 0;
}

