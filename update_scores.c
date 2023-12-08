#include <stdio.h>
#include <stdbool.h>
#include "update_scores.h"
#include "led_matrix.h"

// Function to compare reaction times and update scores
void updateScores(int score_player1, int score_player2) {
    // Display updated scores on LEDs
    displayInteger2(score_player1);
    displayInteger(score_player2);
}
