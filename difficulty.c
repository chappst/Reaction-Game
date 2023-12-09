#include "difficulty.h"
#include "common.h"
#include "interface.h"
#include "reaction_time.h"
#include "joystickSel.h"
#include "RGB.h"
#include "buzzer.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "update_scores.h"
#include "led_matrix.h"
#include "leds.h"

#define NUM_ROUNDS 11

static const RGB rgbColour[] = {
    cRED,
    cGREEN,
    cBLUE,
};

static void choose_RGBled(int colour){

    switch(colour){
        case RED:
            setRGB(cRED);
            break;
        case GREEN:
            setRGB(cGREEN);
            break;
        case BLUE:
            setRGB(cBLUE);
            printf("Setting to blue!\n");
            break;
        default:
            break;
    }
}

static void rand_led_on(int colour){

    switch(colour){
        case 0:
            turn_on_led(RED);
            break;
        case 1:
            turn_on_led(GREEN);
            break;
        case 2:
            turn_on_led(BLUE);
            break;
        default:
            break;
    }
}

static void rand_led_off(){
    turn_off_led(RED);
    turn_off_led(GREEN);
    turn_off_led(BLUE);
}



static void start_game(){
    clearInterface();
    clearMatrix();
    clearMatrix2();
    setRGB(cOFF);
    setBuzzer(30);
    sleepForMs(500);
    setBuzzer(0);
    setRGB(cOFF);
    srand(time(NULL));

    for(int i = 3; i > 0; i--){
        updateScores(i, i);
        sleepForMs(1000);
    }
    
    clearMatrix();
    clearMatrix2();
    sleepForMs(1000);
}


int end_game(int difficulty, int winner){
    //Buzzer goes off again
    setBuzzer(30);
    sleepForMs(500);
    setBuzzer(0);

    //light led of winner
    //display continue screen
    displayContinue(winner);

    int dir;
    do{
        dir = JoystickDirection();
    }while(dir == 0);

    if(JoystickDirection() == 1){
        clearInterface();
        choose_difficulty(difficulty);
        clearMatrix();
        clearMatrix2();
    }else{
        // Go back to main screen
    }
}

int play_easy(){

    start_game();

    int p1Score = 0;
    int p2Score = 0;

    for(int i = 1; i < NUM_ROUNDS+1; i++){
        setRGB(cRED);
        Reaction reaction = start_button_timing(RED);

        if(reaction.timeout){
            i--;
            setRGB(cOFF);
            continue;
        }

        if (reaction.player1 < reaction.player2){
            p1Score++;
            printf("Player 1 wins! Score: %d\n", p1Score);
        }else{
            p2Score++;
            printf("Player 2 wins! Score: %d\n", p2Score);
        }
        setRGB(cOFF);
        updateScores(p1Score, p2Score);
        updateInterface(p1Score, p2Score, i, NUM_ROUNDS);
        sleepForMs(rand()%2500);
    }
    
    updateInterface(p1Score, p2Score, NUM_ROUNDS , NUM_ROUNDS);
    
    return (p1Score > p2Score) ? 1:2; // return who won
}

int play_medium(){

    start_game();

    int p1Score = 0;
    int p2Score = 0;

    for(int i = 1; i < NUM_ROUNDS+1; i++){
        int randCol = rand() % 3; //Randomly choose colour
        choose_RGBled(randCol);
        Reaction reaction = start_button_timing(randCol);

        if(reaction.timeout){
            i--;
            setRGB(cOFF);
            continue;
        }

        if (reaction.player1 < reaction.player2){
            p1Score++;
            printf("Player 1 wins! Score: %d\n", p1Score);
        }else{
            p2Score++;
            printf("Player 2 wins! Score: %d\n", p2Score);
        }
        setRGB(cOFF);
        updateScores(p1Score, p2Score);
        updateInterface(p1Score, p2Score, i, NUM_ROUNDS);
        sleepForMs(rand()%2500);
    }

    updateInterface(p1Score, p2Score, NUM_ROUNDS , NUM_ROUNDS);
    
    return (p1Score > p2Score) ? 1:2; // return who won
}

int play_hard(){

    start_game();

    int p1Score = 0;
    int p2Score = 0;

    for(int i = 1; i < NUM_ROUNDS+1; i++){
        int randCol = rand() % 3; //Randomly choose colour
        rand_led_on(randCol);
        Reaction reaction = start_button_timing(randCol);

        if(reaction.timeout){
            i--;
            rand_led_off();
            continue;
        }

        if (reaction.player1 < reaction.player2){
            p1Score++;
            printf("Player 1 wins! Score: %d\n", p1Score);
        }else{
            p2Score++;
            printf("Player 2 wins! Score: %d\n", p2Score);
        }
        rand_led_off();
        updateScores(p1Score, p2Score);
        updateInterface(p1Score, p2Score, i, NUM_ROUNDS);
        sleepForMs(rand()%2500);
    }

    updateInterface(p1Score, p2Score, NUM_ROUNDS , NUM_ROUNDS);
    
    return (p1Score > p2Score) ? 1:2; // return who won
}

int choose_difficulty(int difficulty){

    clearInterface();

    int winner;

    switch(difficulty){
        case EASY:

            winner = play_easy();
            break;
        case MEDIUM:

            winner = play_medium();
            break;
        case HARD:

            winner = play_hard();
            break;
        default:

            winner = play_easy();
            break;
    }
    return winner;
}