#include <stdio.h>
#include <stdbool.h>
#include "update_scores.h"
#include "led_matrix.h"

// Function to compare reaction times and update scores
void updateScores(int reaction_time_player1, int reaction_time_player2, int *score_player1, int *score_player2) {
    if (reaction_time_player1 < reaction_time_player2) {
        (*score_player1)++; // Player 1 wins the round
    } else if (reaction_time_player2 < reaction_time_player1) {
        (*score_player2)++; // Player 2 wins the round
    }
    // If both players have the same reaction time, no one wins this round

    // Display updated scores on LEDs
    displayInteger(*score_player1);
    displayInteger2(*score_player2);
}
