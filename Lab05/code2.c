#include <stdio.h>

void generateScoringCombinations(int score, int plays[], int playIndex) {
    if (score == 0) {
        // Print the scoring combination
        printf("possible combinations of scoring plays: ");
        for (int i = 0; i < playIndex; i++) {
            if (i > 0) {
                printf(", ");
            }
            if (plays[i] == 6) {
                printf("TD");
            } else if (plays[i] == 3) {
                printf("FG");
            } else if (plays[i] == 2) {
                printf("Safety");
            }
        }
        printf("\n");
    } else if (score < 0) {
        return;
    } else {
        // Try all possible scoring plays
        plays[playIndex] = 6;
        generateScoringCombinations(score - 6, plays, playIndex + 1);

        plays[playIndex] = 3;
        generateScoringCombinations(score - 3, plays, playIndex + 1);

        plays[playIndex] = 2;
        generateScoringCombinations(score - 2, plays, playIndex + 1);

        plays[playIndex] = 8; // TD + 2pt
        generateScoringCombinations(score - 8, plays, playIndex + 1);

        plays[playIndex] = 7; // TD + 1pt FG
        generateScoringCombinations(score - 7, plays, playIndex + 1);
    }
}

int main() {
    int score;
    int plays[50]; // Array to store scoring plays
    int playIndex = 0;

    while (1) {
        printf("Enter the NFL score (enter 0 or 1 to STOP): ");
        scanf("%d", &score);

        if (score <= 1) {
            printf("Program terminated.\n");
            break;
        }

        playIndex = 0;
        generateScoringCombinations(score, plays, playIndex);
    }

    return 0;
}