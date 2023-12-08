#include <stdio.h>
#include <stdlib.h>
#include "joystickSel.h"
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <math.h>

#define A2D_FILE_VOLTAGE2 "/sys/bus/iio/devices/iio:device0/in_voltage2_raw"
#define A2D_FILE_VOLTAGE3 "/sys/bus/iio/devices/iio:device0/in_voltage3_raw"
#define A2D_VOLTAGE_REF_V 1.8
#define A2D_MAX_READING   4095

double Joystick_readY(){
    // Open file
    FILE *f = fopen(A2D_FILE_VOLTAGE2, "r");
    if (!f) {
        printf("ERROR: Unable to open voltage input file. Cape loaded?\n");
        printf(" Check /boot/uEnv.txt for correct options.\n");
        exit(-1);
    }

    // Get reading
    float a2dReading = 0;
    int itemsRead = fscanf(f, "%f", &a2dReading);
    if (itemsRead <= 0) {
        printf("ERROR: Unable to read values from voltage input file.\n");
        exit(-1);
    }

    // Close file
    fclose(f);

    a2dReading = ((2 * a2dReading) / (A2D_MAX_READING) - 1) *1;
    return a2dReading;
}

double Joystick_readX(){
    // Open file
    FILE *f = fopen(A2D_FILE_VOLTAGE3, "r");
    if (!f) {
        printf("ERROR: Unable to open voltage input file. Cape loaded?\n");
        printf(" Check /boot/uEnv.txt for correct options.\n");
        exit(-1);
    }

    // Get reading
    float a2dReading = 0;
    int itemsRead = fscanf(f, "%f", &a2dReading);
    if (itemsRead <= 0) {
        printf("ERROR: Unable to read values from voltage input file.\n");
        exit(-1);
    }

    // Close file
    fclose(f);

    a2dReading = ((2 * a2dReading) / (A2D_MAX_READING) - 1) *1;
    return a2dReading;
}

// Function to check Joystick Direction
int JoystickDirection(){
    double x = Joystick_readX();
    double y = Joystick_readY();

    if (x < -0.5) {
        return 1; // Right
    } else if (x > 0.5) {
        return 2; // Left
    } else if (y > 0.5) {
        return 3; // Down
    } else if (y < -0.5) {
        return 4; // Up
    } else if (x == 0 && y == 0){
        return 0; //Centred
    } else{
        return 0;//(rand() % 4) + 1; // Arbitrarily chosen
    }
}

int JoystickChoice() {
    int choice = 0;
    int difficulty = -1;
    int prevChoice = -1;

    while (1) {
        choice = JoystickDirection();

        if (choice == 3 && prevChoice != 3) {
            displaySelectedDifficulty(difficulty);
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
}


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


void displaySelectedDifficulty(int difficulty) {
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
}

