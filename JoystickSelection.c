#include <stdio.h>
#include <stdlib.h>
#include <JoystickSelection.h>


// Function definitions for displaying difficulty levels
void displayEasy() {
    printf("=== Easy Mode ===\n");
    printf("Instructions for Easy Mode\n");
}

void displayMed() {
    printf("=== Medium Mode ===\n");
    printf("Instructions for Medium Mode\n");
}

void displayHard() {
    printf("=== Hard Mode ===\n");
    printf("Instructions for Hard Mode\n");
}

int choice = 0;
int difficulty = -1;
int prevChoice = -1;

    while (1) {
        choice = JoystickDirection();

        if (choice == 3 && prevChoice != 3) {
            // Select the difficulty when the joystick is toggled downwards
            switch (difficulty) {
                case 0:
                    printf("Selected difficulty: Easy\n");
                    break;
                case 1:
                    printf("Selected difficulty: Hard\n");
                    break;
                case 2:
                    printf("Selected difficulty: Medium\n");
                    break;
                default:
                    printf("No difficulty selected!\n");
                    break;
            }

            break; // Exit the loop after selecting the difficulty
        }

        switch (choice) {
            case 1: // Right
                difficulty = 0; // Set a default value if necessary
                displayEasy();
                break;
            case 2: // Left
                difficulty = 1; // Set a default value if necessary
                displayHard();
                break;
            case 4: // Up
                difficulty = 2; // Set a default value if necessary
                displayMed();
                break;
            case 0: // Centred
                // Handle centred position if needed
                break;
            default:
                // Handle other directions or errors
                break;
        }

        prevChoice = choice;
    }

    return 0;



